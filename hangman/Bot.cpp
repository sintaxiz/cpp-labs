

#include "Bot.h"



char Bot::makeTurn()  {
    return alphabet[currentLetter++];
}

Bot::Bot() {
    alphabet = {'e','a','r','i','o','t','n','s','l','c','u','d', 'p',
                'm','h','g','b','F','y','w','k','v','x','z','j','q'};
    currentLetter = 0;
}
