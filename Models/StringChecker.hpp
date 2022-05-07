#pragma once

#include <cstring>

class StringChecker{

    public:
        #define lowerCaseLetters "abcdefghijklmnopqrstuvwxyz"
        #define upperCaseLetters "ABCDEFGIHJKLMNOPQRSTUVWXYZ"
        #define digits "0123456789"
        #define otherChars "~`!@#$%^&*()_-+={[}]|\\:;\"\'<,>.?/"
        #define emailFormat "@mail.bg"
        #define underscore '_'
        #define jpeg ".jpeg"
        #define png ".png"

        static const bool contains(const char *string, const char symbol){

            const size_t stringSize = strlen(string);
            for(size_t i = 0; i < stringSize; i++)
                if(string[i] == symbol) return true;
            return false;

        }

        static const bool isLower(const char symbol){ return contains(lowerCaseLetters, symbol); }
        static const bool isUpper(const char symbol){ return contains(upperCaseLetters, symbol); }
        static const bool isDigit(const char symbol){ return contains(digits, symbol); }
        static const bool isOther(const char symbol){ return contains(otherChars, symbol); }
        static const bool isUnder(const char symbol){ return symbol == underscore; }
        static const bool isAny(const char symbol){ return isLower(symbol) || isUpper(symbol) || isDigit(symbol) || isOther(symbol); }

        static const bool isPassword(const char *password){

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

        static const bool isEmail(const char *email){

            const size_t emailSize = strlen(email);
            size_t offset = emailSize - strlen(emailFormat);

            for(size_t i = emailSize - 1; i > emailSize - offset - 1; --i)
                if(email[i] != emailFormat[i - offset]) return false;
            
            return true;
            
        }

        static const bool isPng(const char *photo, const size_t photoSize){

            size_t offsetPng = photoSize - strlen(png);

            for(size_t i = photoSize - 1; i != (size_t)(-1); --i)
                if(i >= offsetPng){ if(photo[i] != png[i - offsetPng]) return false; }
                else if(!(isLower(photo[i]) || isUpper(photo[i]) || isUnder(photo[i]))) return false;

            return true;

        }
        static const bool isJpeg(const char *photo, const size_t photoSize){

            size_t offsetJpeg = photoSize - strlen(jpeg);

            for(size_t i = photoSize - 1; i != (size_t)(-1); --i)
                if(i >= offsetJpeg){ if(photo[i] != jpeg[i - offsetJpeg]) return false; }
                else if(!(isLower(photo[i]) || isUpper(photo[i]) || isUnder(photo[i]))) return false;

            return true;

        }

        static const bool isPhoto(const char *photo){

            const size_t photoSize = strlen(photo);
            if(photo[photoSize - 2] == png[2]) return isPng(photo, photoSize);
            if(photo[photoSize - 2] == jpeg[3]) return isJpeg(photo, photoSize);

            return false;

        }

};