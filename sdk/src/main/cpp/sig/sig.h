
#ifndef __SIG_H_
#define __SIG_H_
#include <string>
extern "C" {

/**
 * @brief
 *
 * @param buf
 * @param buf_size
 * @return void* EVP_PKEY
 */
void *ImportEVP_PKEY(const unsigned char *buf, int buf_size);

/**
 * @brief
 *
 * @param buf
 * @param size
 * @return true
 * @return false
 */

bool ExportEVP_PKEY(unsigned char **buf, int *size);

/**
 * @brief
 *
 * @param pkey ImportEVP_PKEY
 * @param message
 * @param size_message
 * @param signature
 * @param size_signature
 * @return true
 * @return false
 */

bool sig_(const void *pkey, const unsigned char *message, int size_message,
          unsigned char **signature, int *size_signature);

/**
 * @brief
 *
 * @param pkey ImportEVP_PKEY
 * @param message
 * @param size_message
 * @param signature
 * @param size_signature
 * @return true
 * @return false
 */
bool verf_(const void *pkey, const unsigned char *message, int size_message,
           unsigned char *signature, int size_signature);


/**
 * @brief
 * 
 * @param str 
 * @return void* 
 */
void *ImportFromHexStr(const char *str);

/**
 * @brief
 * 
 * @param pkey 
 * @param buf 
 * @param size 
 * @return true 
 * @return false 
 */
bool ExportToHexStr(const void *pkey, char **buf, int *size);

/**
 * @brief
 * 
 * @param pkey 
 * @param buf 
 * @param size 
 * @return true 
 * @return false 
 */
bool ExportMnemonic(const void *pkey,char ** buf,int *size);

/**
 * @brief
 * 
 * @param mnemonic 
 * @return void* 
 */
void *ImportFromMnemonic(const char * mnemonic);

void getBase58addr_c(const void * pkey,char **buf,int *size);

void getPriStr_c(const void * pkey,char **buf,int *size);

void getPubStr_c(const void *pkey,char ** buf,int *size);

}
/**
 * @brief Get the Base58 object
 * 
 * @param pkey 
 * @return std::string 
 */
std::string getBase58(const void *pkey);

/**
 * @brief Get the Pub Str object
 * 
 * @param pkey 
 * @return std::string 
 */
std::string getPubStr(const void *pkey);

/**
 * @brief Get the Pri Str object
 * 
 * @param pkey 
 * @return std::string 
 */
std::string getPriStr(const void * pkey);

#endif