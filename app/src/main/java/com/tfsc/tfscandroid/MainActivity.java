package com.tfsc.tfscandroid;

import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import com.google.gson.Gson;
import com.tfsc.sdk.Wallet4Android;
import com.tfsc.tfscandroid.bean.BalanceReq;
import com.tfsc.tfscandroid.bean.TransBeans;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private static Wallet4Android wallet4Android = new Wallet4Android();
    private static Gson gson = new Gson();
    private static final String TAG = "MainActivity";
    private static String DEMO_PRIVATE_KEY = "e5d966990aaadfae56d3e70cdc467725d98e1a76153083babc2d9ee9fab0e6bb";
    private static String DEMO_MNEMONIC = "total sleep play best pupil strong forget language art timber oven entry ocean artwork success plastic lonely sting arena differ panic flash online interest";

    private static String DEMO_FROM_ADDR = "1LW5Z6GDqMs3T9FE67WRKHbdndiK3dWEzx";
    private static String DEMO_TO_ADDR = "1HEUuLH5Zd6Borfu2TccQnEXSBKCEQTBKu";
    private static String TRANS_AMOUNT = "1";

    private static String BASE_URL = "http://192.168.1.42:11190";  //RPC node built by yourself


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.demo_create_new_account).setOnClickListener(this);
        findViewById(R.id.demo_import_account_private_key).setOnClickListener(this);
        findViewById(R.id.demo_import_account_mnemonics).setOnClickListener(this);
        findViewById(R.id.demo_get_balance).setOnClickListener(this);
        findViewById(R.id.demo_transfer).setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        int viewId = view.getId();
        if (viewId == R.id.demo_create_new_account) {
            Log.d(TAG, getString(R.string.demo_create_new_account) + ":" + gson.toJson(wallet4Android.generateKey()));
        } else if (viewId == R.id.demo_import_account_private_key) {
            Log.d(TAG, getString(R.string.demo_import_account_private_key) + ":" + gson.toJson(wallet4Android.importPrivateKey(DEMO_PRIVATE_KEY)));
        } else if (viewId == R.id.demo_import_account_mnemonics) {
            Log.d(TAG, getString(R.string.demo_import_account_mnemonics) + ":" + gson.toJson(wallet4Android.importMnemonicKey(DEMO_MNEMONIC)));
        } else if (viewId == R.id.demo_get_balance) {
            BalanceReq balanceReq = new BalanceReq();
            balanceReq.setType("get_balance");
            balanceReq.setAddr(DEMO_FROM_ADDR);
            OkHttpClient client = new OkHttpClient();
            RequestBody body = RequestBody.create(MediaType.parse("application/json;charset=utf-8"), gson.toJson(balanceReq));
            Request request = new Request.Builder()
                    .url(BASE_URL+"/get_balance")
                    .post(body)
                    .build();
            client.newCall(request).enqueue(new Callback() {

                @Override
                public void onFailure(Call call, IOException e) {
                    Log.e(TAG, "onFailure: " + e);
                }

                @Override
                public void onResponse(Call call, Response response) throws IOException {
                    Log.d(TAG, "response: " + response.body().string());
                    /*The "balance" field divided by 100000000 is the balance
                     {
                     "ErrorCode": "",
                     "ErrorMessage": "",
                     "addr": "",
                     "balance": "3000114097515400",
                     "type": ""
                     }*/

                }
            });

        } else if (viewId == R.id.demo_transfer) {
            TransBeans transBeans = new TransBeans();
            transBeans.setType("tx_req");
            transBeans.fromAddr.add(DEMO_FROM_ADDR);
            transBeans.toAddr.add(new TransBeans.ToAddressBeans(DEMO_TO_ADDR, TRANS_AMOUNT));
            OkHttpClient client = new OkHttpClient();
            RequestBody body = RequestBody.create(MediaType.parse("application/json;charset=utf-8"), gson.toJson(transBeans));
            Request request = new Request.Builder()
                    .url(BASE_URL + "/get_transaction_req")
                    .post(body)
                    .build();
            client.newCall(request).enqueue(new Callback() {
                @Override
                public void onFailure(Call call, IOException e) {
                    Log.e(TAG, "onFailure: " + e);
                }

                @Override
                public void onResponse(Call call, Response response) throws IOException {
                    try {
                        String message = response.body().string();
                        Log.d(TAG, "get_transaction_req : " + message);
                        JSONObject jsonObject = new JSONObject(message);
                        String errorCode = jsonObject.optString("ErrorCode");
                        //ErrorCode is 0 means the request is successful
                        if (!TextUtils.isEmpty(errorCode) && errorCode.equals("0")) {
                            long pKey = wallet4Android.ImportPriHexStr(DEMO_PRIVATE_KEY);//The private key of the from address 1LW5Z6GDqMs3T9FE67WRKHbdndiK3dWEzx
                            String result = wallet4Android.sigTx(pKey, message);
                            OkHttpClient client_send = new OkHttpClient();
                            RequestBody body_send = RequestBody.create(MediaType.parse("application/json;charset=utf-8"), result);
                            Request requset_send = new Request.Builder()
                                    .url(BASE_URL + "/send_message")
                                    .post(body_send)
                                    .build();
                            client_send.newCall(requset_send).enqueue(new Callback() {
                                @Override
                                public void onFailure(Call call, IOException e) {
                                    Log.e(TAG, "send_message onFailure: " + e);
                                }

                                @Override
                                public void onResponse(Call call, Response response) throws IOException {
                                    try {
                                        String result = response.body().string();
                                        Log.d(TAG, "send_message : " + result);
                                        JSONObject jsonObject = new JSONObject(result);
                                        String errorCode = jsonObject.optString("ErrorCode");
                                        if (!TextUtils.isEmpty(errorCode) && errorCode.equals("0")) {
                                            //send Trans Success
                                            /** "txhash" is the hash of this transaction
                                             * {"ErrorCode":"0","ErrorMessage":"","txhash":"ddb85836adf0532694c369dfae3713e70416dad747eb5585414d761212394cf3","type":""}
                                             */
                                            Log.d(TAG, "send_message success: " + result);
                                        }
                                    } catch (JSONException e) {
                                        throw new RuntimeException(e);
                                    }

                                }
                            });
                        }
                    } catch (Exception e) {
                        Log.e(TAG, "Exception: " + e.getMessage());
                    }

                }
            });
        }

    }
}