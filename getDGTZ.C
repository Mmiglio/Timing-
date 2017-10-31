struct acq_data_t {
	ULong64_t	timetag;
	UInt_t		baseline;
	UShort_t 	qshort;
	UShort_t	qlong;
	UShort_t 	pur;
	UShort_t	scope[0];
};

struct acq_params_t {
	UInt_t 		acqTimestamp;
	UShort_t	dppVersion;
	UShort_t	nsPerSample;
	UShort_t	nsPerTimetag;
	UShort_t	numChannels;
	UShort_t 	numSamples[4];
};

struct psd_params_t {
	UInt_t		channel;
	UInt_t		threshold;
	UInt_t 		pretrigger;
	UInt_t		pregate;
	UInt_t		shortgate;
	UInt_t		longgate;
	UInt_t		numSamples;
};

void getPsd_params(TString file_name, int channel){
	
	psd_params_t params_psd;

	TFile *infile = new TFile(file_name);
	TTree *intree = (TTree*)infile->Get("acq_tree_0");
	TBranch *inbranch = intree->GetBranch("psd_params");
	inbranch->SetAddress(&params_psd);

	inbranch->GetEntry(channel);

	cout<<"Psd parameters"<<endl;
	cout<<"*channel = "<<params_psd.channel<<endl;
	cout<<"*threshold = "<<params_psd.threshold<<endl;
	cout<<"*pretrigger = "<<params_psd.pretrigger<<endl;
	cout<<"*pregate = "<<params_psd.pregate<<endl;
	cout<<"*shortgate = "<<params_psd.shortgate<<endl;
	cout<<"*longgate = "<<params_psd.longgate<<endl;
	cout<<"*numSamples = "<<params_psd.numSamples<<endl;

}

void getAcq_params(TString file_name){
	
	acq_params_t params_acq;
	
	TFile *infile = new TFile(file_name);
	TTree *intree = (TTree*)infile->Get("acq_tree_0");
	TBranch *inbranch = intree->GetBranch("acq_params");
	inbranch->SetAddress(&params_acq);

	inbranch->GetEntry(0);

	cout<<"Acquisition parameters: "<<endl;
	cout<<"*acqTimestamp = "<<params_acq.acqTimestamp<<endl;
	cout<<"*dppVersion = "<<params_acq.dppVersion<<endl;
	cout<<"*nsPerSample = "<<params_acq.nsPerSample<<endl;
	cout<<"*nsPerTimetag = "<<params_acq.nsPerTimetag<<endl;
	cout<<"*numChannels = "	<<params_acq.numChannels<<endl;
	cout<<"*numSamples ch0 = "<<params_acq.numSamples[0]<<endl;
	cout<<"*numSamples ch1 = "<<params_acq.numSamples[1]<<endl;
	cout<<"*numSamples ch2 = "<<params_acq.numSamples[2]<<endl;
	cout<<"*numSamples ch3 = "<<params_acq.numSamples[3]<<endl;

	return;
}

void getHistoFromTree(TString file_name, short chan, int nBins, double minX, double maxX){
	
	acq_data_t indata;
	
	TFile *infile = new TFile(file_name);
	TTree *intree = (TTree*)infile->Get("acq_tree_0");
	TBranch *inbranch = intree->GetBranch(Form("acq_ch%d",chan));
	inbranch->SetAddress(&indata);
	
	TH1F *h_timetag = new TH1F("h_timetag","h", nBins, minX, maxX);
	TH1F *h_baseline = new TH1F("h_baseline","h", nBins, minX, maxX);
	TH1F *h_qshort = new TH1F("h_qshort","h", nBins, minX, maxX);
	TH1F *h_qlong = new TH1F("h_qlong","h", nBins, minX, maxX);
	TH1F *h_pur = new TH1F("h_pur","h", nBins, minX, maxX);
	TH1F *h_scope = new TH1F("h_scope","h", nBins, minX, maxX);

	for(int i=0; i<inbranch->GetEntries(); i++){
		inbranch->GetEntry(i);
		h_timetag->Fill(indata.timetag);
		h_baseline->Fill(indata.baseline);
		h_qshort->Fill(indata.qshort);
		h_qlong->Fill(indata.qlong);
		h_pur->Fill(indata.pur);
		h_scope->Fill(indata.scope[0]);
	}

	/*h_timetag->Draw();
	h_baseline->Draw();
	h_qshort->Draw();
	h_qlong->Draw();
	h_pur->Draw();
	h_scope->Draw();*/

	return;
}
