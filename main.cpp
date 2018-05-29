#include <iostream>
#include <sodium.h>
#include <cstring>

#define PASSWORD "Correct Horse Battery Staple"

int main(int argc, char **argv)
{
  
  std::cout << "Hello sodium" << std::endl;

  if (sodium_init() == -1) {
    std::cout << "Sodium not initiated" << std::endl;
  } else {
    std::cout << "Sodium initiated" << std::endl;

    char hashed_password[crypto_pwhash_STRBYTES];
    if (crypto_pwhash_str(
          hashed_password, 
          PASSWORD, 
          strlen(PASSWORD),
          crypto_pwhash_OPSLIMIT_INTERACTIVE, 
          crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
      /* out of memory */
    }

    std::cout << "Hashed pass: " << hashed_password << std::endl;

    if (0 != crypto_pwhash_str_verify(
          hashed_password, 
          PASSWORD, 
          strlen(PASSWORD)
          )) {
      std::cout << "Wrong password" << std::endl;
    }
    else 
    {
      std::cout << "Password OK" << std::endl;
    }

    if(crypto_pwhash_str_needs_rehash(
          hashed_password,
          crypto_pwhash_OPSLIMIT_INTERACTIVE, 
          crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
    {
      std::cout << "It needs rehash" << std::endl;
    }
    else
    {
      std::cout << "It doesn't need rehash" << std::endl;
    }
  }
  
  return 0;
}
