//RotWord() : Function that performs a cyclic permutation i.e., on input [a_i, a_i+1, a_i+2, a_i+3] ouputs [a_i+1, a_i+2, a_i+3, a_i]
word RotWord(word w) {
    word result;
    result.bytes[0] = w.bytes[1];
    result.bytes[1] = w.bytes[2];
    result.bytes[2] = w.bytes[3];
    result.bytes[3] = w.bytes[0];
    return result;
}

//SubWord(): Function on four-byte input word, it applies the S-box
word SubWord(word w) {
    word result;
    result.bytes[0] = SBox[w.bytes[0]];
    result.bytes[1] = SBox[w.bytes[1]];
    result.bytes[2] = SBox[w.bytes[2]];
    result.bytes[3] = SBox[w.bytes[3]];
    return result;
}

//Rcon: Round Constant word-array containing [x^(i-1),{00},{00},{00}] with x^(i-1) being powers of x (x is denoted as {02}) in the field GF(2^8)
word Rcon[] = {
    {0x00, 0x00, 0x00, 0x00}, {0x01, 0x00, 0x00, 0x00}, {0x02, 0x00, 0x00, 0x00}, {0x04, 0x00, 0x00, 0x00},
    {0x08, 0x00, 0x00, 0x00}, {0x10, 0x00, 0x00, 0x00}, {0x20, 0x00, 0x00, 0x00}, {0x40, 0x00, 0x00, 0x00},
    {0x80, 0x00, 0x00, 0x00}, {0x1b, 0x00, 0x00, 0x00}, {0x36, 0x00, 0x00, 0x00}
};

//XorWords(): Function that produce XOR between two 32-bit words
void XorWords(word *a, word *b, word *result) {
    for (int i = 0; i < 4; i++) {
        result->bytes[i] = a->bytes[i] ^ b->bytes[i];
    }
}

//KeyExpansion(): Function that generates a total Nb(Nr+1) words: Nb words for initital key and for each Nr rounds Nb words   
void KeyExpansion(byte key[4*Nk], word w[Nb*(Nr+1)]){
    word temp;
    int i=0;
    
    //Initial key setup
    while (i < Nk) {
        w[i].bytes[0] = key[4*i];
        w[i].bytes[1] = key[4*i+1];
        w[i].bytes[2] = key[4*i+2];
        w[i].bytes[3] = key[4*i+3];
        i++;
    }
    
    //Key Expansion for next Nr rounds
    i=Nk;
    while(i < Nb*(Nr+1)){
        temp = w[i-1];
        if(i % Nk == 0){
            temp = SubWord(RotWord(temp));
            XorWords(&temp, &Rcon[i/Nk], &temp);
        }
        else if (Nk > 6 && i % Nk == 4)
            temp = SubWord(temp);
        XorWords(&w[i-Nk], &temp, &w[i]);
        i++;
    }
    
}
