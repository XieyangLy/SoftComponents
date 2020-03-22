int str_to_int(char *_pStr)
{
    unsigned char flag;
    char *p;
    int ulInt;
    unsigned char i;
    unsigned char ucTemp;

    p = _pStr;
    if (*p == '-')
    {
        flag = 1; /* 负数 */
        p++;
    }
    else
    {
        flag = 0;
    }

    ulInt = 0;
    for (i = 0; i < 15; i++)
    {
        ucTemp = *p;
        if (ucTemp == '.') /* 遇到小数点，自动跳过1个字节 */
        {
            p++;
            ucTemp = *p;
        }
        if ((ucTemp >= '0') && (ucTemp <= '9'))
        {
            ulInt = ulInt * 10 + (ucTemp - '0');
            p++;
        }
        else
        {
            break;
        }
    }

    if (flag == 1)
    {
        return -ulInt;
    }
    return ulInt;
}








