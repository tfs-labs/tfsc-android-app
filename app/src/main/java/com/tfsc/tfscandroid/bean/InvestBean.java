package com.tfsc.tfscandroid.bean;

public class InvestBean extends BaseRequest {

    private String fromAddr;
    private String toAddr;
    private String invest_amount;
    private String investType;
    private String utxo_hash;
    public InvestBean() {

    }

    public String getFromAddr() {
        return fromAddr;
    }

    public void setFromAddr(String fromAddr) {
        this.fromAddr = fromAddr;
    }

    public String getToAddr() {
        return toAddr;
    }

    public void setToAddr(String toAddr) {
        this.toAddr = toAddr;
    }

    public String getInvest_amount() {
        return invest_amount;
    }

    public void setInvest_amount(String invest_amount) {
        this.invest_amount = invest_amount;
    }

    public String getInvestType() {
        return investType;
    }

    public void setInvestType(String investType) {
        this.investType = investType;
    }

    public String getUtxo_hash() {
        return utxo_hash;
    }

    public void setUtxo_hash(String utxo_hash) {
        this.utxo_hash = utxo_hash;
    }
}
