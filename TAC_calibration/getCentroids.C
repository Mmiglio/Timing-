#include "../timing/getDGTZ.C"

void getCentroids(){

	const int dim_array = 7;

	int delay[dim_array]={4, 8, 10, 16, 20, 24, 28};

	TString file_path[dim_array];
	TString file_path0 = "../data_timing/TAC_calibration/delay_";

	TH1F* histo[dim_array];

	ofstream fout("centroids.txt");

	fout<<"#delay (ns)  centroids(channel)   #err centroids(channel)"<<endl;

	for(int i=0; i<dim_array; i++){
		file_path[i]=Form(file_path0+"%ins.root", delay[i]);
		histo[i]=getHistoFromTree(file_path[i], 2, 1026, 0, 50000);

		TSpectrum* s = new TSpectrum(5);
		int nPeaks;
		double *xPeaks;

		nPeaks = s->Search(histo[i], 1, "goff", 0.1);
		if(nPeaks>1) cout<<"Error! more than 1 peak!"<<endl;
		xPeaks = s->GetPositionX();

		//gausian fit
		double intervall=2000;
		double x_fit_min = xPeaks[0]-intervall;
		double x_fit_max = xPeaks[0]+intervall;

		TF1* fit = new TF1("fit", "gaus", x_fit_min, x_fit_max);
		fit->SetParameters(1, xPeaks[0]); //fix the centroid 

		histo[i]->Fit("fit", "Q", "", x_fit_min, x_fit_max);

		cout<<"Delay "<<delay[i]<<"ns"<<endl;
		cout<<"Centroid = "<<fit->GetParameter(1)<<" +/- "<<fit->GetParError(1)<<" (channel)"<<endl;
		cout<<"sigma = "<<fit->GetParameter(2)<<" +/- "<<fit->GetParError(2)<<" (channel)"<<endl;
		cout<<"Chi^2 = "<<fit->GetChisquare()*1.0/((fit->GetNumberFitPoints())-3)<<endl;
		cout<<endl;

		fout<<delay[i]<<"		"<<fit->GetParameter(1)<<"		"<<fit->GetParError(1)<<endl;
		fit->Delete();
	}

	fout.close();
	//save the histo
	TDirectory* currentDir=gDirectory;
	TFile* file_out = new TFile("out.root", "RECREATE");

	for(int i=0; i<dim_array; i++){
		histo[i]->Write();
	}
	
	return;
}