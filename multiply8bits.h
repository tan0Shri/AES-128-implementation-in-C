byte FieldMultiply(byte a, byte b){
    //Initialize the result
    TwoBytes result = 0;
    
    //Loop through each bit of b
    for(int i = 0; i < 8; i++){
        byte temp = b & (1 << i);   //compute the i-th bit of b  in a string of 0's with only ith bit being 1  
        result ^= a * temp;  //multiply a by temp and adding the result with final result
    }
    
    //return the final result
    //return result;
    
    // Reduce modulo the irreducible polynomial x^8 + x^4 + x^3 + x +1 (i.e., 0x11b)
    const unsigned int irreducible =0x11b;
    
    for (int i = 15; i >= 8; i--) {
        if (result & (1 << i)) {
            result ^= irreducible << (i - 8);
        }
    }

    // The result is now reduced modulo x^8 + x^4 + x^3 + x + 1
    return result & 0xFF;
}
