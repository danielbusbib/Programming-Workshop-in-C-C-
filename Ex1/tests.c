//
// Created by bsbdaniel1234 on 24/10/2021.
//

#include "cipher.h"
#define K_2 2
#define K_MIN_5 -5
#define K_28 28
#define K_3 3
#define SUCCESS 1
#define ERROR 0

/**
 * encode tests:
 */
int test_encode_1 ()
{
  char s[] = "abcde", rslt[] = "cdefg";
  encode (s,K_2);
  if (strcmp (s, rslt) == 0)
  {
    return SUCCESS;
  }
  return ERROR;
}

int test_encode_2 ()
{
  char s[] = "aBcYeyZ", rslt[] = "cDeAgaB";
  encode (s, K_2);
  if (strcmp (s, rslt) == 0)
  {
    return SUCCESS;
  }
  return ERROR;
}

int test_encode_3 ()
{
  char s[] = "AnbsB, Edh!$", rslt[] = "ViwnW, Zyc!$";
  encode (s, K_MIN_5);
  if (strcmp (s, rslt) == 0)
  {
    return SUCCESS;
  }
  return ERROR;
}

int test_encode_4 ()
{
  char s[] = "!AnkLq..KzB!", rslt[] = "!CpmNs..MbD!";
  encode (s, K_28);
  if (strcmp (s, rslt) == 0)
  {
    return SUCCESS;
  }
  return ERROR;
}

/**
 * decode tests:
 */
int test_decode_1 ()
{
  char s[] = "jdepq", rslt[] = "hbcno";
  decode (s, K_2);
  if (strcmp (s, rslt) == 0)
  {
    return SUCCESS;
  }
  return ERROR;
}

int test_decode_2 ()
{
  char s[] = "ABkwEac", rslt[] = "XYhtBxz";
  decode (s, K_3);
  if (strcmp (s, rslt) == 0)
  {
    return SUCCESS;
  }
  return ERROR;
}

int test_decode_3 ()
{
  char s[] = "Hdipn - Adqz St! .#fZt@", rslt[] = "Minus - Five Xy! .#kEy@";
  decode (s, K_MIN_5);
  if (strcmp (s, rslt) == 0)
  {
    return SUCCESS;
  }
  return ERROR;
}

int test_decode_4 ()
{
  char s[] = "^1 Jk Vjku $KU @NcUv_Vguv_*!";
  char rslt[] = "^1 Hi This $IS @LaSt_Test_*!";
  decode (s, K_28);
  if (strcmp (s, rslt) == 0)
  {
    return SUCCESS;
  }
  return ERROR;
}
