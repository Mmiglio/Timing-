#include "getDGTZ.C"

void peaksearch(TString file_na) {

	// creare il canvas
	TCanvas *c0 = new TCanvas("c0");
	//c0->Divide(2,2); // to draw more histos on a Canvas (see slides)

	TH1F *h_peaks = getHistoFromTree(file_na,2,1026,0,20000);

	h_peaks->SetTitle("Peak search");

	h_peaks->Draw();

	TSpectrum *s = new TSpectrum(30);
	int nPeaks;
	Double_t *xPeaks;
	int sigma = 1;
	double minratio = 0.9;	// minimum ratio between a peak and the main peak

	nPeaks = s->Search(h_peaks,sigma,"",minratio);

	xPeaks = s->GetPositionX();
	for (int p = 0; p<nPeaks; p++) {
		cout << "Peak #" << p << " @ channel " << xPeaks[p] << endl;	
	}
	
	//Print the result as png image
	//c0->Print(Form("peaks_sigma%i.png",sigma));

}

