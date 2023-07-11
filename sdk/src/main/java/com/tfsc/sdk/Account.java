package com.tfsc.sdk;

public class Account {
    private static final String TAG = "Account";

    private String pri_hex;
    private String pub_hex;
    private String mnemonic;
    private String base58Addr;


    public Account() {

    }

    public Account(String base58Addr, String mnemonic, String pub_hex, String pri_hex) {
        this.base58Addr = base58Addr;
        this.mnemonic = mnemonic;
        this.pub_hex = pub_hex;
        this.pri_hex = pri_hex;
    }

    public String getPri_hex() {
        return pri_hex;
    }

    public void setPri_hex(String pri_hex) {
        this.pri_hex = pri_hex;
    }

    public String getPub_hex() {
        return pub_hex;
    }

    public void setPub_hex(String pub_hex) {
        this.pub_hex = pub_hex;
    }

    public String getMnemonic() {
        return mnemonic;
    }

    public void setMnemonic(String mnemonic) {
        this.mnemonic = mnemonic;
    }

    public String getBase58Addr() {
        return base58Addr;
    }

    public void setBase58Addr(String base58Addr) {
        this.base58Addr = base58Addr;
    }
}
