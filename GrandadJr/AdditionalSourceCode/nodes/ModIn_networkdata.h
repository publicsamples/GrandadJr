namespace project
{

struct ModIn_networkdata: public scriptnode::dll::InterpretedNetworkData
{
	String getId() const override
	{
		return "ModIn";
	}
	bool isModNode() const override
	{
		return false;
	}
	String getNetworkData() const override
	{
		return "514.nT6K8C1RDT7C.XkUIYB.sx1.6SulVZI3QyoTHPNoHsB+voLOfnm1eZppptsaBYEFL7HxT3C.9.fO.T4vdKxIbrA.xZummbhLHvbYO1mNkWZMqG.xbWIkL15MStPC4WqNAB4mHsN8r+CLUhV8pa.4HRZfrD15k6OIRUUwJHHHomo9Aju7RfwNk6QKIO5OwlfJlXS7WLInlAF4UzMncf7+0IefNufvm25fc5Ttsf8Zfr6Y+qUR4R.sg1w6dA+duCs.wt4M5j6VqVvZGdrxRBhkUTziQsS2LX1uRK062ALkAOEUkDjHK+w6BtcexH9HLzLrhQtDjvZRhnrplrh7IpGci12AgzaFQ18oUu5jTLJr4rMsU5.ZoJNrdA0DT2v6lo04M6oPH2M1mBZMgZkKluRFYGk.UAZHoPlxXzrDP.gQA.i..vLmxAP4SByt8wVaQu.mzrEOHXoIK09fwKDIfz2DaLYKl+.CFalFVWuvlWF8qW1ptdvOjhpsBrcc6bRaMvC5bA2HPsEbGWKozCF3LDRROxXKDUY1yNgAa1QxRe116.PeBNMqleVT.haQVlvAVe38KKZQGDgfNVl3vJdgRB1xLt9D3BwrP7LRcaYD032fvN+.4.AIfXkLoGqLALlBI.TTyHtspi96Bf.X9OMhiAaAmaLkBF2.QuaEgxcz4AzNjDE31C";
	}
};
}

