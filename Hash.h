//Simple hash fuc with upper bound set by the user (0,x).
// x = DICTIONARYSIZE - 1


// ΠΑΟΥΛΙΝ ΚΟΜΙΝΙ 202220210090 dit21090@go.uop.gr
// ΒΑΣΙΛΗΣ ΚΟΥΤΑΝΤΟΣ 2022202100097 dit21097@go.uop.gr

unsigned int HASH(char* str, int DICTIONARYSIZE)
{
    unsigned int hash = 0;
    while (*str)
    {
        hash = *str + 31 * hash;
        str++;
    }
    return hash%DICTIONARYSIZE; 
}
