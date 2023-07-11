package com.tfsc.tfscandroid.bean;

import java.util.Vector;

public class TransBeans  extends BaseRequest{

    public static class ToAddressBeans {
        private String addr;
        private String value;

        public ToAddressBeans(String addr_, String value_) {
            addr=addr_;
            value=value_;
        }

        public String getAddr() {
            return addr;
        }

        public void setAddr(String addr) {
            this.addr = addr;
        }

        public String getValue() {
            return value;
        }

        public void setValue(String value) {
            this.value = value;
        }
    }

    public Vector<String> fromAddr;
    public Vector<ToAddressBeans> toAddr;

    public TransBeans(){
        type="tx_req";
        fromAddr=new Vector<String>();
        toAddr=new Vector<ToAddressBeans>();
    }

}

