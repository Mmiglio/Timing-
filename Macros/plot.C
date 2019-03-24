int plot(){

	gROOT->SetStyle("Plain");
	gStyle->SetOptFit(1111);
	gStyle->SetStatBorderSize(0);

	TCanvas* c = new TCanvas();
	//c->SetGrid();

	TGraphErrors graph("sigma_delay.txt", "%lg %lg %lg");
	graph.SetTitle("Time resolution; Delay [ns]; #sigma [ch]");

	graph.SetMarkerStyle(20);
	graph.SetMarkerColor(kBlue);
	graph.SetLineColor(kBlue);

	/*//Define linear function 
	TF1 f("Linear Law","[0]+x*[1]",.5,30.0);

	f.SetLineColor(kRed);
	f.SetLineStyle(2);

	//fit the graph and draw it
	graph.Fit(&f);
	f.DrawClone("Same");*/

	//Draw the graph
	graph.DrawClone("APE");

	return 0;
}