//SubBytes(): Function on four-byte input word, it applies the S-box
word SubBytes(byte state[4][Nb]) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < Nb; c++) {
            state[r][c] = SBox[state[r][c]];
        }
    }
}

//ShiftRows():
void ShiftRows(byte state[4][Nb]){
    byte temp[4];
    for (int r = 1; r < 4; r++){
        for (int c = 0; c < Nb; c++)
            temp[c] = state[r][(c + r) % Nb];
        for (int c = 0; c < Nb; c++)
            state[r][c] = temp[c];
         } 
}

//Mixcolumns
void Mixcolumns(byte state[4][Nb]){
    byte temp[4];
    for (int c = 0; c < Nb; c++) {
        temp[0] = FieldMultiply(0x02, state[0][c]) ^ FieldMultiply(0x03, state[1][c]) ^ state[2][c] ^ state[3][c];
        temp[1] = state[0][c] ^ FieldMultiply(0x02, state[1][c]) ^ FieldMultiply(0x03, state[2][c]) ^ state[3][c];
        temp[2] = state[0][c] ^ state[1][c] ^ FieldMultiply(0x02, state[2][c]) ^ FieldMultiply(0x03, state[3][c]);
        temp[3] = FieldMultiply(0x03, state[0][c]) ^ state[1][c] ^ state[2][c] ^ FieldMultiply(0x02, state[3][c]);
        
        for (int i = 0; i < 4; i++) {
            state[i][c] = temp[i];
        }
    }
}

//AddRoundKey function:
void AddRoundKey( byte state[4][Nb], const word roundKey[Nb]){
    for (int c = 0; c <Nb; c++){
        for(int r = 0; r < 4; r++)
            state[r][c] ^= roundKey[c].bytes[r];
        }
}

// Cipher function
void Cipher(byte in[4 * Nb], byte out[4 * Nb], const word w[Nb * (Nr + 1)]){
    byte state[4][Nb];
    
    //copy input to state array
    for( int i = 0; i < 4; i++){
        for (int j = 0; j < Nb; j++)
            state[i][j] = in[i + 4 * j];
    }
    
    // Initial round key addition
    AddRoundKey(state, w);
    
    //Nr-1 rounds
    for (int round = 1; round < Nr; round++){
        SubBytes(state);
        ShiftRows(state);
        Mixcolumns(state);
        AddRoundKey(state, w + round * Nb);
    }
    
    // Final round (no MixColumns)
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, w + Nr * Nb);
    
    // Copy state array to output
    for( int i = 0; i < 4; i++){
        for (int j = 0; j < Nb; j++)
            out[i + 4 * j] = state[i][j];
    }
    
}
