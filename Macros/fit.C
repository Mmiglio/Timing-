TGraphErrors* residues( TGraphErrors* g, TF1 *f1 );
double func(double* x, double* par){
	return par[1]*x[0]+par[0];
}

double_t start_pt=0, //initial and final points for the fit
	 end_pt=30;

void fit(TString file_name){

	gROOT->Reset();
	gROOT->SetStyle("Plain");
	gStyle->SetOptFit(1111);
	//gStyle->SetOptStat(0);
	gStyle->SetStatBorderSize(0);

	TGraphErrors* graph=new TGraphErrors(file_name, "%lg %lg %lg");

	graph->SetMarkerStyle(20);
	graph->SetMarkerColor(kBlue);
	graph->SetLineColor(kBlue);

	//Defined linear function 
	TF1* f = new TF1("Linear Law",func,start_pt,end_pt,2);

	f->SetLineColor(kRed);
	f->SetLineStyle(2);
	f->SetParNames("q","m");

	//fit the graph and draw it
	graph->Fit(f,"R");


	//Build and draw legend
	TLegend* leg=new TLegend(.1,.7,.3,.9);
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	graph->SetFillColor(0);
	leg->AddEntry(graph,"Exp. Points");
	leg->AddEntry(f,"Linear Fit");
	

	TGraphErrors* res = new TGraphErrors;

	res=residues(graph,f); 


	graph->SetTitle(";;Centroid (channel)");
   	res->SetTitle(";Delay (ns);Residuals");

	TCanvas* c= new TCanvas("c","Residues"/*,200,10,700,500*/);
   	c->Divide(1,2,0,0);
   	//PArtendo da:(xSinistra,ySotto,xDestra,Ysopra) 
    	c->GetPad(1)->SetPad(.005, .30, .995, .96); 
	c->GetPad(2)->SetPad(.005, .03, .995, .30);
    
        c->cd(1);
    	c->GetPad(1)->SetTopMargin(.01);
    	//c->GetPad(1)->SetBottomMargin(.015);
   	c->GetPad(1)->SetBottomMargin(0.0);
   	c->GetPad(1)->SetRightMargin(.01);


	//Draw the graph
	graph->Draw("APE");
	graph->GetXaxis()->SetTickLength(0.03);
	graph->GetXaxis()->SetLabelSize(0);
	graph->GetYaxis()->SetLabelSize(0.04);
	
	graph->GetYaxis()->SetTitleSize(0.06);
	graph->GetYaxis()->SetTitleOffset(0.70);
	graph->GetYaxis()->CenterTitle(); //0.65

	leg->Draw("Same");

   	c->cd(2);
   	c->GetPad(2)->SetGridy();
    	c->GetPad(2)->SetTopMargin(0.0);//.05
    	c->GetPad(2)->SetBottomMargin(.25);
    	c->GetPad(2)->SetRightMargin(.01);

    	res->GetYaxis()->SetTickLength(0.01);
	res->GetYaxis()->SetLabelSize(0.08);
	res->GetYaxis()->CenterTitle();
	

	res->GetXaxis()->SetTickLength(0.03);
	res->GetXaxis()->SetLabelSize(0.1);

	res->GetXaxis()->SetTitleSize(0.15);
	res->GetXaxis()->SetTitleOffset(0.70);
	res->GetXaxis()->CenterTitle();

	res->GetYaxis()->SetTitleSize(0.13);
	res->GetYaxis()->SetTitleOffset(0.30);

	TF1* f1 = new TF1("f1","0*x",start_pt-1,end_pt+1);
	f1->SetLineColor(2);
	f1->SetLineStyle(2);

	res->GetXaxis()->SetLimits(start_pt, end_pt);
	
	res->Draw("APE");
	f1->Draw("Same");

	//c->Print("Prova.eps");

	cout<<endl;
	cout<<"///////////////////////////////"<<endl;
	double m = f->GetParameter(1), q=f->GetParameter(0);
	double sm = f->GetParError(1), sq = f->GetParError(0);
	cout<<"y = mx+ q"<<endl;
	cout<<"m = "<<m<<" +- "<<sm<<" ch/ns"<<endl;
	cout<<"q = "<<q<<" +- "<<sq<<" ch"<<endl;
	cout<<"///////////////////////////////"<<endl; 

	cout<<"-----Conversion-----"<<endl;
	double centroid1=48950, centroid0=34500;
	cout<<"T2-T1 = "<<(centroid1-centroid0)/m<<" ns "<<endl;
	cout<<"c = "<<1.564*2.0/(((centroid1-centroid0)/m)*pow(10,-9))<<" m/s"<<endl;
	//cout<<"c = "<<2*1.638/(((centroid1-centroid0)/m)*pow(10,-9))<<" m/s"<<endl; //metodo 2
}



TGraphErrors* residues( TGraphErrors* g, TF1 *f1 ){

	int N=g->GetN();

	TGraphErrors* r = new TGraphErrors(N,g->GetX(),g->GetY(),NULL,g->GetEY());
	r->SetMarkerStyle(g->GetMarkerStyle());
	r->SetMarkerColor(g->GetMarkerColor());
	r->SetMarkerSize(g->GetMarkerSize());
	r->SetLineColor(g->GetLineColor());
	r->SetLineWidth(g->GetLineWidth());

	TGraphErrors* corr = new TGraphErrors();

	int j=0;

	r->SetName("Residues");

	for(int i=0; i<N; ++i){

		double xi = r->GetX()[i];
		double yi = r->GetY()[i];

		if( (xi < start_pt) || ( xi>end_pt ) ){
			r->SetPoint(i,-10.,0.);
			//r->RemovePoint(i);
		}
		else{
			double delta = yi - f1->Eval( xi );
			r->SetPoint(i,xi,delta);
			double err_res = sqrt( pow( r->GetEY()[i] ,2) + pow( (f1->GetParameter(1))*(r->GetEX()[i]) ,2) );
			r->SetPointError(i,0.0,err_res);
			corr->SetPoint(j,xi,yi);
			j++;
		}
	}

	cout<<endl;
	cout<<"///////////////////////////////"<<endl;
	cout<<"Correlation: "<<  corr->GetCorrelationFactor()<<endl;
	cout<<"///////////////////////////////"<<endl;

	return r;
}
