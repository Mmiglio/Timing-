#include "../timing/getDGTZ.C"

void delay_cable(){

	const int dim_array = 6;

	int cable_length[dim_array]={115, 215, 500, 605, 800, 1000};

	TString file_path[dim_array];
	TString file_path0 = "../data_timing/delay_cable_calibration/cable_";

	TH1F* histo[dim_array];

	ofstream fout("results.txt");

	fout<<"#cable_length (mm)  delay (ns)   err delay(ns)"<<endl;

	//delay unit 8ns data
	double centroid_8ns = 14968.2, err_centroid_8ns = 1.18504;

	//calibration stuff
	double m = 1360.16, err_m = 0.055209;

	for(int i=0; i<dim_array; i++){
		file_path[i]=Form(file_path0+"%imm.root", cable_length[i]);
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

		histo[i]->Fit("fit", "QN", "", x_fit_min, x_fit_max);


		double c = fit->GetParameter(1) - centroid_8ns;
		double err_c = sqrt( pow( fit->GetParError(1) ,2 )+pow( err_centroid_8ns ,2) );

		double conversion = c / m;
		double err_conversion = sqrt( pow( err_c/m , 2 ) + pow( c*err_m / (m*m) , 2 ) );

		fout<<cable_length[i]<<"		"<<conversion<<"		"<<err_conversion<<endl;
		fit->Delete();
	}

	fout.close();
	
	return;
}