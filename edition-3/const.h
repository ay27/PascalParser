#pragma once

#include <string>
using namespace std;

#define  PROG_SIZE     10000


//��ʶ������
#define  NONE     0
#define  NUMBER   1
#define  VARIABLE   2
#define  DELIMITER  3
#define  STR        4
#define  KEYWORD    5
#define  PTYPE      6

//�ؼ���
#define  UNKNOW   0
#define  VAR      1
#define  FOR      2
#define  TO       3
#define  BEGIN    4
#define  END      5
#define  READ     6
#define  WRITE    7
#define  WRITELN  8
#define  IF       9
#define  THEN     10
#define  DO       11

//�������ͷ�
#define  INTEGER  1
#define  REAL     2
#define  CHAR     3


//������
const string EOL = "\n";
const string EOP = "end.";

const int Key_size = 12;


