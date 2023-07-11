#include "sigTx.h"
#include "google/protobuf/util/json_util.h"
#include "../envelop/base58.h"
#include "sig.h"
#include "../envelop/debug.h"
#include "../envelop/tx.h"

#include <set>
std::string testSig(CTransaction& tx ,void * pkey) {
	auto txUtxo = tx.mutable_utxo();
	int index = 0;
	std::set<std::string> Mirset;
	auto vin = txUtxo->mutable_vin();
	for (auto& owner : txUtxo->owner()) {
		Mirset.insert(owner);
		auto vin_t = vin->Mutable(index);
		std::string serVinHash = getsha256hash(vin_t->SerializeAsString());
		std::string signature;
		std::string pub;
		unsigned char* signature_c = nullptr;
		int size;
		
		bool ret=sig_(pkey, (const unsigned char*)serVinHash.c_str(), serVinHash.size(), &signature_c, &size);
		signature = std::string((const char *)signature_c, size);
		free(signature_c);
		pub = getPubStr(pkey);
		
		if (ret==false) {
			debugL("sign fail ");
		}


		CSign* vinSign = vin_t->mutable_vinsign();
		vinSign->set_sign(signature);
		vinSign->set_pub(pub);
		index++;
	}
	for (auto& owner : Mirset) {

		CTxUtxo* txUtxo = tx.mutable_utxo();
		CTxUtxo copyTxUtxo = *txUtxo;
		std::string serTxUtxo = getsha256hash(copyTxUtxo.SerializeAsString());
		std::string signature;
		std::string pub;
		unsigned char* signature_c = nullptr;
		int size;

		bool ret = sig_(pkey, (const unsigned char*)serTxUtxo.c_str(), serTxUtxo.size(), &signature_c, &size);
		signature = std::string((const char*)signature_c, size);
		free(signature_c);
		pub = getPubStr(pkey);
		if (ret == false) {
			debugL("sign fail ");
		}
		CSign* multiSign = txUtxo->add_multisign();
		multiSign->set_sign(signature);
		multiSign->set_pub(pub);
	}
	return "0";
}


std::string toSig(const std::string& data,void * pkey) {
	tx_ack ack;
	ack.paseFromJson(data);
	CTransaction tx_t;
	google::protobuf::util::Status status = google::protobuf::util::JsonStringToMessage(ack.txJson, &tx_t);

	testSig(tx_t,pkey);

	std::string txJsonString;
	status = google::protobuf::util::MessageToJsonString(tx_t, &txJsonString);
	ack.txJson = txJsonString;
	return ack.paseToString();
}
