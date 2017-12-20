/*

 * consoletetris.c

 *
 *  Created on: 2014/01/08
 *      Author: Kamiya Cristian

 */

/* インクルードヘッダ */

#include <stdio.h>   /* Standard IO */
#include <stdlib.h>  /* Standard Library */
#include <string.h>  /* String */
#include <time.h>    /* Time: ランダムの生成のために必要 */
#include <termios.h> /* TermiOS: 非同期通信のための汎用ターミナルインターフェース  */
#include <unistd.h>  /* UNIX標準定数・型 */
#include <fcntl.h>   /* ファイルコントロール */

#define BLOCKS 7      /* ブロックの種類 */
#define ONEPOINT 100  /* 1行のみのポイント */
#define TWOPOINT 400  /* 同時消し2行のポイント */
#define THRPOINT 900  /* 同時消し3行のポイント */
#define FORPOINT 1600 /* 同時消し4行のポイント */
#define FPS      2000 /* 落下速度調整: Macだと2000, Unixだと1500くらい？ */

/* グローバル変数 */
int stage[21][12]; /* [ゲーム画面中のブロックの情報を格納するための配列] */
int block[4][4];   /* [生成されるブロックの種類（形）を格納するための配列] */
int field[21][12]; /* [ゲーム画面中の固定済みブロック（下にブロックが固定されている状態）全体の情報を格納するための配列] */
int block_list[BLOCKS][4][4] = { /* ７種類のブロックのデータ */
  { { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 } },   /* I */ 														
  { { 0, 0, 0, 0 }, { 0, 1, 1, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 } },   /* L */ 														
  { { 0, 0, 1, 0 }, { 0, 1, 1, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, 0 } },   /* 逆S */ 													
  { { 0, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 0 } },   /* S */ 														
  { { 0, 0, 0, 0 }, { 0, 1, 0, 0 }, { 1, 1, 1, 0 }, { 0, 0, 0, 0 } },   /* T */ 														
  { { 0, 0, 0, 0 }, { 0, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 0 } },   /* O */ 														
  { { 0, 0, 0, 0 }, { 0, 1, 1, 0 }, { 0, 0, 1, 0 }, { 0, 0, 1, 0 } } }; /* 逆L */


int lvspeed[15] = { 200, 180, 160, 140, 120, 105, 90, 75, 60, 50, 40, 30, 20, 15, 10 }; /* 落下速度 */
int y = 0;         /* ブロックの画面上でのy座標 */
int x = 4;         /* ブロックの画面上でのx座標 */
int oneline, twoline, threeline, fourline; /* 消したラインの数 */
int gameover = 0;  /* ゲームオーバー判定。新しいブロックが初期位置に置けなければ1になる。 */
int nextblock = 0; /* [次に生成するブロックの種類(形)をランダムで生成するため、乱数を利用し、その乱数を所持する外部変数] */
int block_type;    /* ブロックの種類用。0~6の乱数を入れる */
int level = 1;     /* [レベルについての外部変数、現在のゲームのレベルを納める] */
int point = 0;     /* [全体(ゲーム)の点数を保存し、格納するための外部変数] */
int toffset = 0;   /* 最下段までブロックが行った時に下ボタンを押した時に加算されるタイマー */

/* 関数プロトタイプ宣言 */											
void Initialize();          /* ゲーム起動直後の初期設定を行う関数。画面と壁のデータを初期化 */
int CreateBlock();          /* 新しいブロックを生成して次のブロックに発生させるための関数 */
void ShowGameField();       /* fieldの中身に応じて画面を描画する関数 */
void ControlBlock();        /* キー入力に応じてブロックに移動や回転などの処理を行わせるための関数 */
int CheckOverlap(int, int); /* 落下中のブロックが壁や固定済みブロックに接触していないか判別する関数 */
void MoveBlock(int, int);   /* 落下中ブロックを一旦消して、任意の座標を移動させるための関数 */
int TurnRightBlock();       /* ブロックの右回転を処理する関数 */
int TurnLeftBlock();        /* ブロックの左回転を処理する関数 */
void DropBlock();           /* ブロックを落下させる。下に移動できない場合ブロックをその位置に固定 */
void LockBlock();           /* 着地したブロックを固定済みブロックに加える関数 */
void CheckLines();          /* ブロックが横一列にそろえばそこを消去後、上のブロックをそこに下ろす */
int kbhit();                /* キーボードを1回ヒットしたかどうかの判定 */
int GetTimeOfLevel(int);    /* レベル毎の時間設定 */
void GameStart();           /* ゲームスタート時のスプライト表示 */


/*

 * メイン関数

 */

int main() {

  /* キーボードの入力を隠すための処理 */ 
  system("stty echo -icanon min 1 time 0");

  /* 時間をカウント */

  int time = 0;

  /* [GameStart()関数の呼び出し:最初のゲームスタート時のスプライト表示をするために呼出す。] */

  GameStart();

  /* [Initialize()関数の呼び出し:ゲーム起動直後の初期設定を行う。画面と壁のデータを初期化をするために、初めに呼び出しておく。] */

  Initialize();

  /* [gameoverが1（真）でない間、ループ。（ゲームがゲームオーバーでない間にループ）] */

  while (!gameover) {

    /* キー入力があればそれに応じて操作 */

    if (kbhit()) {

      ControlBlock();

    }

    /* [現在のレベルに応じた時間経過でなければ分岐し、レベルに応じた時間経過に設定するための処理を行う。] */

    if (time < GetTimeOfLevel(level)) {

      time += toffset + 1; /* 時間経過 */

      toffset = 0;

    } else {

      DropBlock(); /* [Drop()関数の呼び出し:ブロックを落下させる（下に移動できない場合ブロックをその位置に固定する）ために呼出す] */

      time = 0;
    }

  }

  /* キーボードの入力設定を元に戻す */

  system("stty echo icanon min 1 time 0");

  return 0;
}

/*

 *  [ゲーム起動直後の初期設定を行う関数。画面と壁のデータを初期化を行う関数。戻り値、引数はなし。]
 *  Initialize()

 */
																		
void Initialize() {
																		
  int i, j; /* forループ制御用変数 */

  /* [ゲーム画面の枠組を描写（初期化）する] */
 
  for (i = 0; i <= 20; i++) {

    for (j = 0; j <= 11; j++) {

      if ((j == 0) || (j == 11) || (i == 20)) {

	field[i][j] = stage[i][j] = 9;

      } else {

	field[i][j] = stage[i][j] = 0;

      }

    }

  }
														
  /* [次に生成するブロックをランダムにするための乱数発生。] */

  srand((unsigned) time(NULL ));

  nextblock = rand() % 7;

  /* [CreateBlock()関数の呼び出し:新しいブロックを生成して次のブロックに発生させる為に、乱数を発生させたあとで呼出す。] */
  CreateBlock();
  /* [ShowGameField()関数の呼び出し:field[][]の中身に応じて、画面を描画する。] */
  ShowGameField();

}

/*

 *  [新しいブロックを生成して次のブロックに発生させる]

 *  CreateBlock()

 *  帰り値: [新しいブロックを生成できず、ゲームオーバーの場合は1,新しいブロックを生成し、正常に動作できたときは、0を返す]

 */

int CreateBlock() {

  int i, j; /* forループ制御用の変数 */

  /* ブロックの座標を初期位置にリセット */

  y = 0;
  x = 4;
  
  /* [ブロックの種類を格納] */
  block_type = nextblock;

  //srand((unsigned)time(NULL));

  nextblock = rand() % 7;

  /* [ブロックの種類（形）を格納するための処理。] */

  for (i = 0; i < 4; i++) {

    for (j = 0; j < 4; j++) {

      block[i][j] = 0;

      block[i][j] = block_list[block_type][i][j];

    }

  }

  /* [フィールドに次の新しいブロックを生成して描写する。] */

  for (i = 0; i < 4; i++) {

    for (j = 0; j < 4; j++) {

      field[i][j + 4] = stage[i][j + 4] + block[i][j];

      /* [もし、ブロックが上で重なり、枠を超えてしまった場合、ゲームオーバーと判定する。(変数gameoverのフラグを立てる。)] */

      if (field[i][j + 4] > 1) {

	gameover = 1;

	return 1;

      }

    }

  }

  return 0;

}

/*

 *  [field[][]の中身に応じて、画面を描画する関数。戻り値、引数なし] 

 *  ShowGameField()

 */

void ShowGameField() { 																				
  int i, j; /* forループ制御用変数 */ 																		
																								
  /* 画面を一旦クリア */ 																			
  system("clear"); 																				
																								
  /* [ゲーム画面をfield[][]の中身に応じて、ループにより描写する。] */ 																			
  for (i = 0; i < 21; i++) { 																			
    for (j = 0; j < 12; j++) { 																		
      
      switch (field[i][j]) { 																		
      case 0: 																				
	printf("　"); 																			
	break; 																			
      case 9: 																				
	printf("囗"); 																			
	break; 																			
      default: 																				
	printf("圖"); 																			
	break; 																			
      } 																					
    } 																						
		
    /* 右サイド表示部分 */ 																			
    /* 2-7行目: 次ブロック   */ 																		
    if (i == 1) 																				
      printf("　　囗ＮＥＸＴ囗"); 																		
    else if (i >= 2 && i <= 5) { 																		
      printf("　　囗"); 																			
      for (j = 0; j < 4; j++) { 																		
	switch (block_list[nextblock][i - 2][j]) { 															
	case 0: 																			
	  printf("　"); 																		
	  break; 																			
	default: 																			
	  printf("圖"); 																		
	  break; 																			
	} 																				
      } 																					
      printf("囗"); 																			
    } else if (i == 6) 		
      printf("　　囗囗囗囗囗囗"); 																		
    
    /* 9行目～14行目 操作説明 */ 																		
    else if (i == 8) 																			
      printf("　　←　右移動"); 																		
    else if (i == 9) 																			
      printf("　　→　左移動"); 																		
    else if (i == 10)
      printf("　　↓　下移動"); 																		
    else if (i == 11)
      printf("　　Ｚキー　左回転"); 																	
    else if (i == 12)
      printf("　　Ｘキー　右回転"); 																	
    else if (i == 13)
      printf("　　Ｑキー　終了");

    /* 16行目～18行目 レベルとスコア表示 */ 																	
    else if (i == 15) 																			
      printf("　　囗囗囗ＳＣＯＲＥ囗囗囗"); 																	
    else if (i == 16) 																			
      printf("　　囗 LV:%2d/%10d 囗", level, point); 																
    else if (i == 17) 																			
      printf("　　囗囗囗囗囗囗囗囗囗囗囗"); 																	
    
    /* 各行の改行 */

    printf("\n");

  }

  /* [それぞれの行消しの回数をゲームプレイ中に表示する。] */

  printf("\n１行消し：%d回 ２行消し：%d回 ３行消し：%d回 ４行消し：%d回\n", oneline, twoline,threeline, fourline);

  /* [gameoverになったら、結果を表示する。（gameover=1のとき）] */

  if (gameover) {

    system("clear");

    printf("\nYour Lines:\n１行消し：%d回 ２行消し：%d回 ３行消し：%d回 ４行消し：%d回\nYour Level: %d\nYour Scoure: %12d\n\nGAME OVER\n\n", oneline, twoline, threeline, fourline, level, point);
  }

}

/*

 * [キー入力に応じてブロックに移動や回転等の処理を行わせる]

 * ControlBlock()

 */

void ControlBlock() { 																				
  char key; /* [キーボードからの入力を保存するchar型変数keyの宣言] */
  
  /* [キーボードからの入力を変数keyに保存] */																	
  key = getchar(); 																				

  /* キーに応じて各方向へブロックを移動したり、回転させたりする */ 															
  /* qキー: ゲーム終了（強制GameOver） */ 																	
  /* zキー: ブロック左回転                          */ 																
  /* xキー: ブロック右回転                          */ 																
  /* ←キー: 左移動 (ESC]C)        */ 																		
  /* →キー: 右移動 (ESC]D)        */ 																		
  /* ↓キー: 下移動 (ESC]B)        */ 																		
  switch (key) { 																					
  case 'q': 																						
    gameover = 1; 																				
    ShowGameField(); 																			
    break; 																					
  case 'z': 																						
    TurnLeftBlock(); 																			
    break; 																					
  case 'x': 																						
    TurnRightBlock(); 																			
    break; 																					
  case 27: 																						
    key = getchar(); 																			
    if (key == 91) { 																			
      key = getchar(); 																			
      switch (key) { 																			
      case 'B': /* Down */ 																		
	if (!CheckOverlap(x, y + 1)) { 																	
	  MoveBlock(x, y + 1); 																	
	} else { 																			
	  toffset = 300 * FPS; /* 一番下まで行たときに下ボタン押したら次のブロック */ 											
	} 																				
	break; 																			
      case 'C': /* Left */ 																		
	if (!CheckOverlap(x + 1, y)) { 																	
	  MoveBlock(x + 1, y); 																	
	} 																				
	break; 																			
      case 'D': /* Right */ 																		
	if (!CheckOverlap(x - 1, y)) { 																	
	  MoveBlock(x - 1, y); 																	
	} 																				
	break; 																			
      default: 																				
	break; 																			
      } 																					
    } 																						
    break; 																					
  default: 																						
    break; 																					
  } 																							
} 																								

/* [関数コメント例] 																					
 * 被りのチェックを行う関数 																			
 * CheckOverlap() 																					
 * 戻り値: int: もし壁等に被る場合 = 1, それ以外 = 0. 																	
 * 引数: int x2: ブロックを格納している4x4の配列の左上のx座標 																
 * int y2:  ブロックを格納している4x4の配列の左上のy座標 																
 */
 																								
int CheckOverlap(int x2, int y2) { 																			
  int i, j; /* forループ制御用変数 */ 																		
  
  /* [壁に被っているかどうかの判定をする処理。もし壁などに被ってしまっている場合は、1を返す] */ 																			
  for (i = 0; i < 4; i++) { 																			
    for (j = 0; j < 4; j++) { 																		
      if (block[i][j]) { 																			
	if (stage[y2 + i][x2 + j] != 0) { 																
	  return 1; 																		
	} 																				
      } 																					
    } 																						
  } 																							
  return 0; 																						
} 																								

/*																
 * 落下中ブロックを一旦消して、任意の座標に移動させるための関数
 * MoveBlock()								
 * 引数: int x2: ブロックを格納している4x4の配列の左上のx座標 																
 * int y2:  ブロックを格納している4x4の配列の左上のy座標 
 */
																				
void MoveBlock(int x2, int y2) {

  int i, j; /* forループ制御用変数 */
  
  /* [落下しているブロックの情報をいったん消す] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] -= block[i][j];
    }
  }

  /* [引数を外部変数(x:ブロックの画面上でのx座標y:ブロックの画面上でのy座標)に代入する。] */ 																			
  x = x2; 																						
  y = y2; 																						
  
  /* [落下したブロックの情報から、ゲーム画面を新たに描写するために、field[][]の中身を更新する。] */ 																			
  for (i = 0; i < 4; i++) { 																			
    for (j = 0; j < 4; j++) { 																		
      field[y + i][x + j] += block[i][j]; 																	
    } 																						
  } 																							
  
  /* [ShowGameField()関数の呼び出し:更新したfield[][]の中身に応じて、画面を新たに描画するために関数を呼び出す。] */ 																			
  ShowGameField();  												
}																					

/* 																								
 * [ブロックの右回転を処理する関数] 																				
 * TurnRightBlock() 																					
 * 戻り値: [呼びだし元に値0を返し、制御を呼びだし元に戻す。] 																			
 * ブロック右回転の重なりチェックはこの中で行っている . 																
 * 壁蹴り1マス分実装（但し、テトリス棒は除く. 																	
 */
 																								
int TurnRightBlock() { 																				
  int i, j; /* forループ制御用 */ 																		
  int tmp[4][4]; /* [ブロックを右回転させるための配列を宣言。一時的に回転させるブロックの情報を格納し、回転処理を行うため。] */ 																	
  int offset = 0; 																					
																								
  /* [ブロックを右回転させるために、配列tmpに保存する。] */ 																			
  for (i = 0; i < 4; i++) { 																			
    for (j = 0; j < 4; j++) { 																		
      tmp[i][j] = block[i][j]; 																		
    } 																						
  } 																							
  
  /* [ブロックを右回転させる処理。] */ 																			
  for (i = 0; i < 4; i++) { 																			
    for (j = 0; j < 4; j++) { 																		
      block[i][j] = tmp[3 - j][i]; 																		
    } 																						
  } 																							
  
  /* [CheckOverlsp()関数による判定。落下中のブロックが壁などに接触していないかのどうかを、右回転させる際に確認するための分岐。] */ 																			
  if (CheckOverlap(x, y)) { 																			
    /* 壁蹴り左壁 */ 																			
    if (!CheckOverlap(x + 1, y) && block_type != 0) 																
      offset = 1; 																			
    /* 壁蹴り右壁 */ 																			
    else if (!CheckOverlap(x - 1, y) && block_type != 0) 															
      offset = -1; 																			
		/* ダメだと戻す */ 																			
    else { 																					
      for (i = 0; i < 4; i++) { 																		
	for (j = 0; j < 4; j++) { 																	
	  block[i][j] = tmp[i][j]; 																	
	} 																				
      } 																					
      return 1; 																				
    } 																						
  } 																							
																								
  /* [回転前のブロックの情報を一旦消す] */ 																			
  for (i = 0; i < 4; i++) { 																			
    for (j = 0; j < 4; j++) { 																		
      field[y + i][x + j] -= tmp[i][j]; 																	
    } 																						
  } 																							
  /* 壁蹴り分の移動 */ 																				
  x = x + offset; 																					
  
  /* [回転したあとのブロックの情報から、新たにゲーム画面を描写するための処理。] */ 																			
  for (i = 0; i < 4; i++) { 																			
    for (j = 0; j < 4; j++) { 																		
      field[y + i][x + j] += block[i][j]; 																	
    } 																						
  } 																							
  
  /* [ShowGameField()関数の呼び出し:更新したfield[][]の中身に応じて、画面を新たに描画するために関数を呼び出す。] */ 																			
  ShowGameField();
  return 0; 																						
} 																								

/* 																								
 * [ブロックの左回転を処理する]

 * TurnLeftBlock()

 * 戻り値: [呼びだし元に値0を返し、制御を呼びだし元に戻す。]

 * ブロック左回転の重なりチェックはこの中で行っている.

 * 壁蹴り1マス分実装（但し、テトリス棒は除く.)

 */

int TurnLeftBlock() {

  int i, j; /* forループ制御用 */

  int tmp[4][4]; /*[ブロックを左回転させるための配列を宣言。一時的に回転させるブロックの情報を格納し、回転処理を行うため。]*/

  int offset = 0;

  /* [ブロックを左回転させるために、配列tmpに回転前のブロックの情報を一時的に保存する。] */
  for (i = 0; i < 4; i++) {

    for (j = 0; j < 4; j++) {

      tmp[i][j] = block[i][j];

    }

  }

  /* [ブロックを左回転させるための処理。] */

  for (i = 0; i < 4; i++) {

    for (j = 0; j < 4; j++) {
      block[i][j] = tmp[j][3 - i];

    }

  }

  /* [CheckOverlsp()関数による判定。落下中のブロックが壁などに接触していないかのどうかを、左回転させる際に確認するための分岐。] */

  if (CheckOverlap(x, y)) {

    /* 壁蹴り左壁 */

    if (!CheckOverlap(x + 1, y) && block_type != 0)

      offset = 1;
    /* 壁蹴り右壁 */
    else if (!CheckOverlap(x - 1, y) && block_type != 0)
      offset = -1;

    /* ダメだと戻す */

    else {
      for (i = 0; i < 4; i++) {
	for (j = 0; j < 4; j++) {
	  block[i][j] = tmp[i][j];
	}
      }
      return 1;
    }
  }
  
  /* [回転前のブロックの情報を一旦消す] */

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] -= tmp[i][j];
    }
  }

  /* 壁蹴り分の移動 */
  x = x + offset;
  
  /* [回転したあとのブロックの情報から、ゲーム画面を新たに描写するための処理。] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] += block[i][j];
    }
  }

  /* [ShowGameField()関数の呼び出し:更新したfield[][]の中身に応じて、画面を新たに描画するために関数を呼び出す。] */
  ShowGameField();
  
  return 0;

}

/*
 * [ブロックを落下させる。下に移動できない場合ブロックをその位置に固定]
 * DropBlock()
 */

void DropBlock() {

  /* [ブロックを動かせるかどうかの判定をCheckOverLap()関数により判定する。動かせる場合はMoveBlock()関数を呼び出す。] */
  if (!CheckOverlap(x, y + 1)) {
    MoveBlock(x, y + 1);
  }

  /* [動かせない場合は、以下の３つの関数を呼び出し、それぞれ処理を行う。] */
  else {
    LockBlock();
    CreateBlock();
    ShowGameField();
  }
}

/*
 * [着地したブロックを固定済みブロックに加えるための関数 引数、戻り値ともになし]
 * LockBlock()
 */

void LockBlock() {
  int i, j; /* forループ制御用変数 */

  /* [固定済みブロックの情報を新らた（着地したあとの新たなゲーム画面のこと）に追加] */
  for (i = 0; i < 21; i++) {
    for (j = 0; j < 12; j++) {
      stage[i][j] = field[i][j];
    }
  }

  /* [CheckLines()関数の呼び出し:ブロックが横一列にそろえばそこを消去後、上のブロックをそこに下ろす処理を着地したあとに行うために呼び出す。] */
  CheckLines();

  /* [ライン消去後の画面を更新するための処理。固定済みブロックの情報を新たにfield[][]の中身に格納する。] */
  for (i = 0; i < 21; i++) {
    for (j = 0; j < 12; j++) {
      field[i][j] = stage[i][j];
    }
  }
}

/*

 * [ブロックが横一列にそろえばそこを消去後、上のブロックをそこに下ろすための関数　戻り値、引数ともになし]

 * CheckLines()

 */

void CheckLines() {

  int i, j, k; /* forループ制御用 */

  int comp; /* 横一列がそろっていれば１、一つでも隙間があると０になる */
  int lines = 0; /* 同時に消したラインの数 */
  
  while (1) {

    for (i = 0; i < 20; i++) {

      comp = 1;

      /* [ループにより、隙間がないかのチェック。もしある場合はcomp=0とする。] */

      for (j = 1; j < 11; j++) { 																		
	if (stage[i][j] == 0) { 																	
	  comp = 0;
	}
      }
      /* [もしcompが1であれば（隙間がなければ）break] */ 																		
      if (comp == 1) 																			
	break; 																			
    } 																						
    /* [もしcompが0であれば（隙間を発見したら）break] */ 																		
    if (comp == 0) 																				
      break; 																				
    
    /* [行数をインクリメント] */
    lines++;

    /* [stage[i][j]のすべての要素を0に初期化する] */
    for (j = 1; j < 11; j++) {
      stage[i][j] = 0;
    }

    /* [ブロックを消した行数だけ下におろすための処理。] */
    for (k = i; k > 0; k--) {
      for (j = 1; j < 11; j++) {
	stage[k][j] = stage[k - 1][j];
      }
    }
  }

  /* [消した行数を計算し、行消しの数を保存するための外部変数にそれぞれ代入する。] */ 																			
  switch (lines) { 																				
  case 1: 																						
    oneline++; 																					
    break; 																					
  case 2: 																						
    twoline++; 																					
    break; 																					
  case 3: 																						
    threeline++; 																				
    break; 																					
  case 4: 																						
    fourline++; 																				
    break; 																					
  default: 																						
    break; 																					
  } 																							
  
  /* [ポイントを消した行数に応じて計算する。] */ 																			
  point = oneline * 100 + twoline * 400 + threeline * 900 + fourline * 1600; 														
  /* [レベルを計算する] */ 																			
  level = (int) (point / 2000.0) + 1; 																		
  /* [レベルが15より大きい場合、レベルを15のままにする。（レベルに15の上限をつけるため）] */ 																			
  if (level > 15)

    level = 15;

}

/*

 *  キーボードが押されたかどうかの判定を返す関数

 * kbhit()

 * 返り値: キーボードが押された場合 = 1, 他 = 0

 * この関数は難しいので、『そういうものだ』としてください

 */

int kbhit(void) {

  struct termios oldt, newt; /* termosで保持する構造体 */
  int ch;                    /* 確認する文字 */
  int oldf;                  /* ファイル状態 */

  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);   /* ファイル操作状態の取得 */

  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); /* 文字取得状態待ちの解除 */

  ch = getc(stdin); /* 文字取得 */
  fcntl(STDIN_FILENO, F_SETFL, oldf);      /* ファイル操作の状態を元に戻す（Unlock） */
  /* 文字が取得されたかどうかを検査 */

  if (ch != EOF) {

    ungetc(ch, stdin); /* 文字がとれていたら判定のために文字をバッファに戻す */

    return 1;

  }

  return 0;

}

/*

 * [レベル毎の時間設定を行う関数]

 * GetTimeOfLevel

 * 戻り値: [レベル毎に時間設定した落下速度]

 * 引数: [関数呼び出し時のゲームのレベル]

 */

int GetTimeOfLevel(int level) {

  if (level >= 1 && level <= 15)

    return FPS * lvspeed[level - 1];

  else

    return 5 * FPS;

}

/*

 * [Gamestart()関数：戻り値、引数ともにvoid. ゲームスタート時のスプライト表示をするための関数]
 * GameStart()

 */

void GameStart() {

  FILE* fp; /* [ファイルポインタfpの宣言] */

  char string[60]; /* [文字列string[60]の宣言、ファイルの内容を記憶するため] */

  char sprite[1000]; /* [文字列sprite[1000]の宣言,ファイルの内容を記憶するため] */

  char ch; /* getchar()（一文字入力関数）の戻り値を持つためのchar型変数chの宣言 */

  int ret;

  int flag = 1; /* ゲームセンターっぽく点滅させるためのフラグ管理 */

  int time = 9999; /* タイマー */

  /* [ファイルsprite.txtの読み込み] */

  fp = fopen("sprite.txt", "r");

  /* [ファイルの内容を読み込む] */

  fscanf(fp, "%s", sprite);

  while ((ret = fscanf(fp, "%s", string)) != EOF) {

    strcat(sprite, "\n");

    strcat(sprite, string); /* [文字列spriteと文字列stringの連結をする。] */

  }

  /* [ファイルのクローズ] */
  fclose(fp);

  /* スプライト表示 */

  while (1) {

    /* タイマーがカンストするたびに更新  */

    if (time > 80 * FPS) {

      /* 一度消去 */

      system("clear");

      /* [ファイルから文字列spriteに読み込んだ内容を標準出力に出力する。] */

      printf("%s\n\n", sprite);

      /* プログラミングコースのクレジット */

      printf("\n    2012 Programming C Course\n\n");

      if (flag == 1) {

	/* 点滅させる所 */

	printf("     PUSH SPACE KEY TO START\n");

      }

      /* 点滅フラグ */
      flag *= -1;

      /* タイマーを戻す */
      time = 0;

    }

    /* キーレスポンスの設定 */

    if (kbhit()) {

      ch = getchar();

      if (ch == 'q') { /* もしキーボードからqが入力されたら、gameover判定のためのフラグをたてて、breakする（ゲーム終了の判定） */
	gameover = 1;

	break;
      } else if (ch == ' ') { /* キーボードから空白（スペース）が入力されたらbreak（ゲームスタート時の判定） */

	break;
      }

    }

    /* タイマーをインクリメント */

    time++;

  }

  /* [戻り値なしで、ゲームスタート関数を終了させる] */

  return;

}
