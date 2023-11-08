#include "interface.h"
#include "../envelop/debug.h"
#include "../sig/sig.h"
#include "../sig/sigTx.h"
#include <cstring>
#include "../envelop/base64.h"
#include "../evmone/evmc.h"
#include "../log.h"


long long  import_base64_prikey_handler(const char *buf, int buf_size){
        infoL(buf);
        std::string dbase=FromBase64(buf,buf_size);
        debugL(dbase);
        return (long long)ImportEVP_PKEY((const unsigned char *)dbase.c_str(),dbase.size());
    }

  char *  export_new_prikey_base64(){
         unsigned char * buf=NULL;
         int size_=0;
        ExportEVP_PKEY(&buf, &size_);
        char * buffer=toBase64((const char *)buf,size_);
        return (char *)buffer;
    }

  // __declspec(dllexport)  char* __stdcall sig_go( long long pkey, const char  *message, int size_message){
  //       unsigned char * buf=NULL;
  //       int size_=0;
  //       sig_((const void *)pkey, (const unsigned char *)message,  size_message, &buf, &size_);
  //       char * buffer=toBase64((const char *)buf,size_);
  //       return buffer;
  //   }

    // __declspec(dllexport) int __stdcall verf_go( long long pkey, const char  *message, int size_message,const char * nature,int nature_size){
    //     std::string dbase=FromBase64(nature,nature_size);
    //     bool ret= verf_((const void *)pkey, (const unsigned char *)message, size_message,
    //       ( unsigned char *)dbase.c_str(), dbase.size());
    //     return (int)ret;
    // }

    long long   import_prikey_handler_from_hex(const char *str){
        return (long long)ImportFromHexStr(str);
    }

    char *  export_new_prikey_to_hex(long long pkey){
        char * buf=NULL;
        int size_=0;
        ExportToHexStr((const void *)pkey, &buf, &size_);
        return buf;
    }

    char *  export_mnemonic_from_prikey_handler(long long pkey){
        char * buf=NULL;
        int size_=0;
        ExportMnemonic((const void *)pkey, &buf, &size_);
        return buf;
    }

    long long  import_prikey_handler_from_mnemonic(const char * mnemonic){
        return (long long)ImportFromMnemonic(mnemonic);
    }

    char *  get_base58addr(long long pkey){
        char * buf=NULL;
        int size_=0;
        getBase58addr_c((const void *)pkey, &buf, &size_);
        return buf;
    }

 char *  get_pubstr_base64(long long pkey){
        char * buf=NULL;
        int size_=0;
        //getPubStr_c((const void *)pkey, &buf,&size_);
        std::string ret=getPubStr((const void *)pkey);
        Base64 base_;
        std::string res=base_.Encode((const unsigned char *)ret.c_str(), ret.size());
        buf=(char *)malloc(res.size()+1);
        buf[res.size()]=0;
        memcpy(buf, res.c_str(), res.size());
        return buf;
    }


   char *  sig_tx(long long pkey,const char * message,int msize){
       std::string msg(message,msize);
       std::string res=toSig(msg, (void *)pkey);
       char * buf=(char *)malloc(res.size()+1);
       buf[res.size()]=0;
       memcpy(buf,res.c_str(),res.size());
       return buf;
    }

      void  free_prikey_handler(long long pkey){
        free_pkey((const void *)pkey);
    }


char * get_base58_from_evm(const char * evmAddr){
    std::string ret= evm_utils::EvmAddrToBase58(std::string(evmAddr));
    char * value=new char[ret.size()+1];
    memcpy(value, ret.c_str(), ret.size());
    value[ret.size()]=0;
    return value;
}

char *get_evmaddr_from_pubstr(const char * pubstr,int pubstr_size){
    auto evm_addr_s= evm_utils::pubStrToEvmAddr(std::string(pubstr,pubstr_size));
    auto rets=evm_utils::EvmAddrToString(evm_addr_s);
    char * value=new char[rets.size()+1];
    memcpy(value, rets.c_str(), rets.size());
    value[rets.size()]=0;
    return value;
}

//bool sig_contract_tx(const void *pkey, const unsigned char *message, int msize, unsigned char **signature,
//                     int *size_signature) {
//    std::string msg((char *)message, msize);
//    std::string res = toSig(msg, (void *) pkey);
//    unsigned char *buf = (unsigned char *) malloc(res.size() + 1);
//    buf[res.size()] = 0;
//    memcpy(buf, res.c_str(), res.size());
//
//    *size_signature = res.size();
//    *signature = buf;
//    return true;
//}