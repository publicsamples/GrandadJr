namespace project
{

struct cables_networkdata: public scriptnode::dll::InterpretedNetworkData
{
	String getId() const override
	{
		return "cables";
	}
	bool isModNode() const override
	{
		return false;
	}
	String getNetworkData() const override
	{
		return "387.nT6K8CVxGz7B.XVz4PB.KqS.uPhQ11L0gw.zfnRXRuCuCnsgAEfvtz+qi+wOi1wvV5mK.3B.v.PreX77AsVCzeYxR1hvoEqfi99BFQ0+.sGz+fXxXO4x1QgsVAzW8nQOCQXCyNR.UzZrwtLIVkp+7jqxztLLPGM5SGGHhAty1CMmxQ+kMZigibnE.8WsTxYaM9EqmDkznWAzDkhERKjnVD5iZPGzwikG1TCF2CVvwTfNKKA6mQVxeDBqi9L806gpWF6JAPEIkXRZRgzhDLjXLU.UBSmFWoqhxvP99vf3nW0KHlM.8slimLs52C5XQr0XyXmACrCngDGIxHSXJnLK0Ap..n53F.d3HsEnjYJMmlCor7AQIyTaNMWp6voKBM8CKfpMSAA4XPVRdjmMa.fLDfl4KwHgu2xQPE5Ewd9OYMfjIn7vMZSVAUlrpJcwYG7wj4LVLAXvf6KzoBH8xSvByESflfBX6TxQU7e28phtt3BW82o8pap15AX7D1AtyCTLf+e.";
	}
};
}

