#include "StringChecker.hpp"

const bool StringChecker::contains(const char *string, const char symbol){

    const size_t stringSize = strlen(string);
    for(size_t i = 0; i < stringSize; i++)
        if(string[i] == symbol) return true;
    return false;

}

const bool StringChecker::isPassword(const char *password){

    bool hasLowerCase = false, hasUpperCase = false, hasDigit = false, hasOtherChar = false;
    
    const size_t passwordSize = strlen(password);
    for(size_t i = 0; i < passwordSize; i++){

        if(hasLowerCase && hasUpperCase && hasDigit && hasOtherChar) break;

        hasLowerCase = hasLowerCase || StringChecker::isLower(password[i]);
        hasUpperCase = hasUpperCase || StringChecker::isUpper(password[i]);
        hasDigit     = hasDigit     || StringChecker::isDigit(password[i]);
        hasOtherChar = hasOtherChar || StringChecker::isOther(password[i]);

    }

    return hasLowerCase && hasUpperCase && hasDigit && hasOtherChar;

}

const bool StringChecker::isEmail(const char *email){

    const size_t emailSize = strlen(email);
    size_t offset = emailSize - strlen(EMAILFORMAT);

    for(size_t i = emailSize - 1; i > emailSize - offset - 1; --i)
        if(email[i] != EMAILFORMAT[i - offset]) return false;
    
    return true;
    
}

const bool StringChecker::isPng(const char *photo, const size_t photoSize){

    size_t offsetPng = photoSize - strlen(PNG);

    for(size_t i = photoSize - 1; i != (size_t)(-1); --i)
        if(i >= offsetPng){ if(photo[i] != PNG[i - offsetPng]) return false; }
        else if(!(isLower(photo[i]) || isUpper(photo[i]) || isUnder(photo[i]))) return false;

    return true;

}

const bool StringChecker::isJpeg(const char *photo, const size_t photoSize){

    size_t offsetJpeg = photoSize - strlen(JPEG);

    for(size_t i = photoSize - 1; i != (size_t)(-1); --i)
        if(i >= offsetJpeg){ if(photo[i] != JPEG[i - offsetJpeg]) return false; }
        else if(!(isLower(photo[i]) || isUpper(photo[i]) || isUnder(photo[i]))) return false;

    return true;

}

const bool StringChecker::isPhoto(const char *photo){

    const size_t photoSize = strlen(photo);
    if(photo[photoSize - 2] == PNG[2]) return isPng(photo, photoSize);
    if(photo[photoSize - 2] == JPEG[3]) return isJpeg(photo, photoSize);

    return false;

}