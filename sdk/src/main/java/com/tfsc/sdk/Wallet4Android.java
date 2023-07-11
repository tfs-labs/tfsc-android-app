package com.tfsc.sdk;

public class Wallet4Android {
    static {
        System.loadLibrary("rpc4Android");
    }

    public native long importPkey(String key);

    public native String newPkey();

    public native String GetBase58(long pKey);

    public native String GetPubStr(long pKey);


    public native String sigTx(long pKey, String message);

    public native String ExportPriHexStr(long pKey);

    public native long ImportPriHexStr(String message);

    public native String ExportMnemoic(long pKey);

    public native long ImportMnemoic(String message);


    public Account generateKey() {
        String base = newPkey();
        if (!base.equals("NULL")) {
            long importPkey = importPkey(base);
            if (importPkey != 0) {
                String base58 = GetBase58(importPkey);
                String pubKey = GetPubStr(importPkey);
                String priKey = ExportPriHexStr(importPkey);
                String mnemoic = ExportMnemoic(importPkey);
                return new Account(base58, mnemoic, pubKey, priKey);
            } else {
                return new Account();
            }
        } else {
            return new Account();
        }
    }

    public Account importPrivateKey(String privateKey) {
        long importPkey = ImportPriHexStr(privateKey);
        if (importPkey != 0) {
            String base58 = GetBase58(importPkey);
            String pubKey = GetPubStr(importPkey);
            String mnemoic = ExportMnemoic(importPkey);
            return new Account(base58, mnemoic, pubKey, privateKey);
        } else {
            return new Account();
        }
    }

    public Account importMnemonicKey(String mnemonic) {
        long importPkey = ImportMnemoic(mnemonic);
        if (importPkey != 0) {
            String base58 = GetBase58(importPkey);
            String pubKey = GetPubStr(importPkey);
            String priKey = ExportPriHexStr(importPkey);
            return new Account(base58, mnemonic, pubKey, priKey);
        } else {
            return new Account();
        }

    }
}
