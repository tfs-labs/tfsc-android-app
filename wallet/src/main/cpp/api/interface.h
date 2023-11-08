#ifdef __cplusplus
extern "C" {

#endif
/*导入私钥句柄*/
/**
 * @brief 
 * 
 * @param buf 私钥base64字符串
 * @param buf_size 长度
 * @return long long 
 */
long long import_base64_prikey_handler(const char *buf, int buf_size);

char *export_new_prikey_base64();
/**
 * @brief 
 * 
 * @param str 私钥十六进制字符串
 * @return long long 
 */
long long import_prikey_handler_from_hex(const char *str);

/**
 * @brief 
 * 
 * @param pkey 私钥句柄
 * @return char* 
 */
char *export_new_prikey_to_hex(long long pkey);
/**
 * @brief 
 * 
 * @param pkey 私钥句柄
 * @return char* 
 */
char *export_mnemonic_from_prikey_handler(long long pkey);
/**
 * @brief 
 * 
 * @param mnemonic 助记词
 * @return long long 
 */
long long import_prikey_handler_from_mnemonic(const char *mnemonic);
/**
 * @brief Get the base58addr object
 * 
 * @param pkey 私钥句柄
 * @return char* 
 */
char *get_base58addr(long long pkey);
/**
 * @brief Get the pubstr base64 object
 * 
 * @param pkey 私钥句柄
 * @return char* 
 */
char *get_pubstr_base64(long long pkey);

/**
 * @brief 
 * 
 * @param pkey 私钥句柄
 * @param message 交易体
 * @param msize 交易体长度
 * @return char* 
 */
char *sig_tx(long long pkey, const char *message, int msize);
/**
 * @brief 
 * 
 * @param pkey 私钥句柄
 */
void free_prikey_handler(long long pkey);
/**
 * @brief Get the base58 from evm object
 * 
 * @param evmAddr evm地址
 * @return char* 
 */
char * get_base58_from_evm(const char * evmAddr);
/**
 * @brief Get the evmaddr from pubstr object
 * 
 * @param pubstr 公钥二进制
 * @param pubstr_size 二进制长度
 * @return char* 
 */
char *get_evmaddr_from_pubstr(const char * pubstr,int pubstr_size);

//bool sig_contract_tx(const void *pkey,  const unsigned char *message, int msize,unsigned char **signature,
//                     int *size_signature);

#ifdef __cplusplus
}
#endif