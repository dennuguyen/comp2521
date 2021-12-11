int isSameWord(char *a, char *b)
{
    if (strlen(a) != strlen(b))
        return FALSE;

    while (*a && *b)
    {
        if (*a++ != *b++)
            return FALSE;
    }

    if ((*a && !*b) || (*b && !*a))
        return FALSE;

    return TRUE;
}