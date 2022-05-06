//boolTokenizing numbers
Value *numboolToken(char charRead) {
    char *fullnumber = talloc(301); //input cannot be longer than 300 chars
    int doubleCheck = 0;
    int numSize = 0;
    if (charRead == '+' || charRead == '-') {
      fullnumber[0] = charRead; //add
      numSize++;
      char symbolsign = charRead;
      charRead = (char)fgetc(stdin);

      if (!isdigit(charRead)) {
        charRead = ungetc(charRead, stdin);
        charRead = ungetc(symbolsign, stdin); //add back +/- since not number
        return symbolHelp(charRead);
      }
    }

    while (isdigit(charRead) || charRead == '.') { //int or double
        if (charRead == '.') {
            doubleCheck = 1; //is a double
        }
        fullnumber[numSize] = charRead;
        numSize++;
        charRead = (char)fgetc(stdin);
    }

    fullnumber[numSize] = '\0'; //end of num
    char *endptr;
    Value *newboolToken = talloc(sizeof(Value));
    if (doubleCheck) {
        newboolToken->type = DOUBLE_TYPE;
        newboolToken->d = strtod(fullnumber, &endptr);
    } else {
        newboolToken->type = INT_TYPE;
        newboolToken->numSize= strtod(fullnumber, &endptr);
    }
    ungetc(charRead, stdin);
    return newboolToken;
}


// boolean
Value *boolToken(char readChar) {
  Value *newboolToken = talloc(sizeof(Value));
  newboolToken->type = BOOL_TYPE;
  int *boolToken = talloc(sizeof(int) * 2);
  
  if (readChar == 'f') {
    boolToken [0] = '#f';
    boolToken [1] = '\0';
    newboolToken->i = *boolToken;
  } else if (readChar == 't') {
    boolToken [0] = '#t';
    boolToken [1] = '\0';
    newboolToken->i = *boolToken;
  } else {
    printf("Syntax error: untokenizeable \n");
    texit(0);
  }
  return newboolToken;
}