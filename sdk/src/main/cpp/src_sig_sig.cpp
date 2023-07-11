
#include "src_sig_sig.h"
#include "../envelop/debug.h"
#include "jni.h"
#include "../sig/sig.h"
#include "../envelop/base64.h"
#include <cstdlib>
#include <string>
#include "jni_tools.h"
#include "../sig/sigTx.h"
#include "log.h"

/*
 * Class:     src_sig_sig
 * Method:    importPkey
 * Signature: (Ljava/lang/String;)J
 */
extern "C" JNIEXPORT jlong JNICALL Java_com_tfsc_sdk_Wallet4Android_importPkey
  (JNIEnv * env, jobject, jstring str){
        std::string temp=jstring2string(env, str);
        Base64 base_;
        std::string prikey=base_.Decode(temp.c_str(), temp.size());
        void * pkey=ImportEVP_PKEY((const unsigned char *)prikey.c_str(),prikey.size());
        return (jlong)pkey;
  }

/*
 * Class:     src_sig_sig
 * Method:    newPkey
 * Signature: ()Ljava/lang/String;
 */
extern "C" JNIEXPORT jstring JNICALL Java_com_tfsc_sdk_Wallet4Android_newPkey
  (JNIEnv *env , jobject){
    unsigned char * buf_;
    int size=0;
    Base64 base_;
    std::string retvalue;
    bool ret=ExportEVP_PKEY(&buf_, &size);

    if(ret==false){
        errorL("ExportEVP_PKEY error");
       return  env->NewStringUTF("NULL");
        
    }
    retvalue=base_.Encode(buf_, size);
    //free(buf_);
    return env->NewStringUTF(retvalue.c_str());

  }

/*
 * Class:     src_sig_sig
 * Method:    sigmessage
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
extern "C" JNIEXPORT jstring JNICALL Java_com_tfsc_sdk_WalletRpc_sigmessage
  (JNIEnv * env, jobject, jlong pkey, jstring message){
        void * pkey_t=(void *)pkey;
        std::string message_=jstring2string(env, message);
        unsigned char *signa=nullptr;
        int size=0;
        Base64 base_;
       bool ret_b= sig_((const void *)pkey_t,(const unsigned char *)message_.c_str(),message_.size(),&signa,&size);
        if(ret_b==false){
            errorL("sig_");
            return env->NewStringUTF("NULL");
        }
        std::string res=base_.Encode((const unsigned char *)signa,size);
        free(signa);
        return env->NewStringUTF(res.c_str());
  }

/*
 * Class:     src_sig_sig
 * Method:    vefmessage
 * Signature: (JLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_tfsc_sdk_vefmessage
  (JNIEnv *env, jobject, jlong pkey, jstring message, jstring signature){
        Base64 base_;
        std::string temp=jstring2string(env, signature);
        std::string message_=jstring2string(env, message);
        std::string sign_=base_.Decode(temp.c_str(), temp.size());
        void * pkey_t=(void *)pkey;
        bool ret=verf_((const void *)pkey_t, (const unsigned char *)message_.c_str(), message_.size(), (unsigned char *)sign_.c_str(), sign_.size());
        return (jboolean)ret;
  }

extern "C" JNIEXPORT jstring JNICALL Java_com_tfsc_sdk_Wallet4Android_sigTx(JNIEnv *env, jobject, jlong pkey, jstring tx)
  {
     std::string tx_t=jstring2string(env, tx);
     std::string res=toSig(tx_t,(void *) pkey);
      return env->NewStringUTF(res.c_str());
  }


extern "C" JNIEXPORT jstring JNICALL Java_com_tfsc_sdk_Wallet4Android_GetBase58
  (JNIEnv *env , jobject, jlong pkey){
        void * pkey_t=(void *)pkey;
        std::string ret=getBase58((const void *)pkey_t);
        return env->NewStringUTF(ret.c_str());
  }


extern "C" JNIEXPORT jstring JNICALL Java_com_tfsc_sdk_Wallet4Android_GetPubStr
  (JNIEnv *env, jobject, jlong pkey){
       void * pkey_t=(void *)pkey;
       std::string ret=getPubStr(pkey_t);
       Base64 base_;
      std::string ep=  base_.Encode((const  unsigned char *)ret.c_str(), ret.size());
      return env->NewStringUTF(ep.c_str());
  }




  /*
 * Class:     src_sig_sig
 * Method:    ExportPriHexStr
 * Signature: (J)Ljava/lang/String;
 */
extern "C" JNIEXPORT jstring JNICALL Java_com_tfsc_sdk_Wallet4Android_ExportPriHexStr
  (JNIEnv *env, jobject, jlong pkey){
      char * buf=nullptr;
      int size=0;
      bool ret= ExportToHexStr((void *)pkey, &buf, &size);
      if(ret==false){
         errorL("ExportToHexStr fail");
      }
      std::string buffer(buf,size);
      free(buf);
      return env->NewStringUTF(buffer.c_str());
  }

/*
 * Class:     src_sig_sig
 * Method:    ImportPriHexStr
 * Signature: (Ljava/lang/String;)J
 */
extern "C" JNIEXPORT jlong JNICALL Java_com_tfsc_sdk_Wallet4Android_ImportPriHexStr
  (JNIEnv *env, jobject, jstring hexStr){
      std::string hexStr_s=jstring2string(env, hexStr);
      void * pkey=ImportFromHexStr(hexStr_s.c_str());
      return (jlong)pkey;
  }

/*
 * Class:     src_sig_sig
 * Method:    ExportMnemoic
 * Signature: (J)Ljava/lang/String;
 */
extern "C" JNIEXPORT jstring JNICALL Java_com_tfsc_sdk_Wallet4Android_ExportMnemoic
  (JNIEnv *env , jobject, jlong pkey){
    char * buf=nullptr;
    int size=0;
     bool ret= ExportMnemonic((void *)pkey, &buf, &size);
     if(ret==false){
        errorL("ExportMnemonic fail");
     }
     std::string mne(buf,size);
     free(buf);
     return env->NewStringUTF(mne.c_str());
  }

/*
 * Class:     src_sig_sig
 * Method:    ImportMnemoic
 * Signature: (Ljava/lang/String;)J
 */
extern "C" JNIEXPORT jlong JNICALL Java_com_tfsc_sdk_Wallet4Android_ImportMnemoic
  (JNIEnv *env, jobject, jstring Mnstr){
      std::string Mnestr=jstring2string(env, Mnstr);
      void * pkey= ImportFromMnemonic(Mnestr.c_str());
      return (jlong)pkey;
  }