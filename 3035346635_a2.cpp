//SOURAV PRAKASH PADHIARI, 3035346635

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
using namespace std;

struct travel_promo
{
	string dest, ai;
	int fromd, tod, price, dends, quotal, search; 
};
struct code_country
{
	string code, country;
	int revenue, tickets ;
};

void readDataP (travel_promo plist[], ifstream &DB, int &i)
{
	
	string dummy, line; 
	getline(DB, dummy, ',');		//header: destination 
	getline(DB, dummy ,',');		//header: airline
	getline(DB, dummy, ',');		//header: fromdate
	getline(DB, dummy, ',');		//header: todate
	getline(DB, dummy, ',');		//header: price
	getline(DB, dummy, ',');		//header: dealends
	getline(DB, dummy);				//header: quotaleft

	
	while (DB.good())
	{	
		getline(DB, plist[i].dest, ',');
		getline(DB, plist[i].ai, ',');
		
		string tfromd, ttod, tprice, tdends, tquotal;
		getline (DB, tfromd, ',' );
		getline (DB, ttod, ',' );
		getline (DB, tprice, ',' );
		getline (DB, tdends, ',' );
		getline (DB, tquotal);

		stringstream temp1, temp2, temp3, temp4, temp5;

		temp1 << tfromd;
		temp1 >> plist[i].fromd;
		temp2 << ttod;
		temp2 >> plist[i].tod;
		temp3 << tprice;
		temp3 >> plist[i].price;
		temp4 << tdends;
		temp4 >> plist[i].dends;
		temp5 << tquotal;
		temp5 >> plist[i].quotal;
		i++;
	}	

}

void command_all(travel_promo plist[], int i)
{
	for ( int j=0; j<i; j++ )
	{	cout << "[" << j+1 << "]" << " " << plist[j].dest << "-" << plist[j].ai << "-" << plist[j].fromd << "-" << plist[j].tod << " ";
		cout << "HKD" << " " << plist[j].price << "," << " promotion expires " << plist[j].dends << ", " ;
		cout << plist[j].quotal << " " << "quota" << endl;
	}	
	cout << "total " << i << " records"<< endl;  
}

void command_buy(travel_promo plist[], int i, int kc, code_country clist[], int c)
{
	string buy_line;
	int tickets_purchased;
	cin >> buy_line;
	cin >> tickets_purchased;
	int temp1=0; 
	

	int targeti;
	if (buy_line[0] != '#')
	{	
		for (int j=0; j<i ; j++)
		{	string a,b,c;
			stringstream temp1, temp2, temp3;
			temp1 << plist[j].fromd; temp1 >> a;
			temp2 << plist[j].tod; temp2 >> b;
			temp3 << plist[j].price; temp3 >> c; 
			
			if (buy_line == (plist[j].dest+"-"+plist[j].ai+"-"+a+"-"+b+"-"+c))
			 	targeti = j;
				
		}
		if ((plist[targeti].quotal - (tickets_purchased)) < 0)
			cout << "not enough tickets" << endl;
		else
		{	plist[targeti].quotal = (plist[targeti].quotal - (tickets_purchased));
			cout << tickets_purchased << " ticket (s) purchased" << endl;
			temp1=(plist[targeti].price * tickets_purchased * 0.9);
			for (int a=0; a<c; a++)
			{	if (clist[a].code==plist[targeti].dest)
				{	clist[a].revenue=clist[a].revenue+temp1;
					clist[a].tickets=clist[a].tickets+tickets_purchased;
				}	
			}		
		}	

	}


	else
	{	buy_line=buy_line.substr(1,(buy_line.length()-1));
		stringstream temp4; int k;
		temp4<<buy_line; temp4>>k;
		for (int j=0; j<i; j++)	
		{	if (plist[j].search==k)
			{	targeti=j;
				if ((plist[targeti].quotal - (tickets_purchased)) < 0)
				cout << "not enough tickets" << endl;
				else
				{	plist[targeti].quotal = (plist[targeti].quotal - (tickets_purchased));
					cout << tickets_purchased << " ticket (s) purchased" << endl;
					temp1=(plist[targeti].price * tickets_purchased * 0.9);
					for (int a=0; a<c; a++)
					{	if (clist[a].code==plist[targeti].dest)
						{	clist[a].revenue=clist[a].revenue+temp1;
							clist[a].tickets=clist[a].tickets+tickets_purchased;
						}
					}		

				}
			}	
		}		
		
	}	

	


}

void command_search(travel_promo plist[], int i, int &kc)
{	int k;
	string s1, search_line;
	cin >> s1 >> search_line;
	if (s1=="dest")
	{	for (int j=0; j<i; j++)
		{	if (search_line==plist[j].dest)
			{	kc++;
				for(k=kc-1; k<kc; k++)
				{	cout << "<" << k+1 << ">" << plist[j].dest << "-" << plist[j].ai << "-" << plist[j].fromd<< "-";
					cout << plist[j].tod << "-" << "HKD" << " " << plist[j].price << "," << " promotion expires ";
					cout << plist[j].dends << ", " << plist[j].quotal << " " << "quota" << endl;
					plist[j].search=k+1;

				}	
			

			}
				

		}
		
	}
	else
	{	stringstream temp;
		temp << search_line;
		int a;
		temp >> a;

		for (int j=0; j<i; j++)
		{	if ((a >= plist[j].fromd) &&	(a <= plist[j].tod))
			{	kc++;
				for(k=kc-1; k<kc; k++)
				{	cout << "<" << k+1 << ">" << plist[j].dest << "-" << plist[j].ai << "-" << plist[j].fromd<< "-";
					cout << plist[j].tod << "-" << "HKD" << " " << plist[j].price << "," << " promotion expires ";
					cout << plist[j].dends << ", " << plist[j].quotal << " " << "quota" << endl;
					plist[j].search=k+1;
				}
				
			}
		}

	}
						
}
int DtFrmt(string date);

void command_addpromo (travel_promo plist[], int &i)
{	string useless;
	cin >> useless;
	string filename;
	cin >> filename; 
	ifstream add; 
	add.open(filename.c_str());
	if (add.fail())
		cout << "error opening Add Promotion file " << endl;
	string dummy;
	string airline;	
	
	getline(add, dummy, ':');
	getline(add, airline);
	
	while (add.good())
	{	string line, tdealends;
		getline(add, line);
		if (line.substr(0,4)=="deal")
		{	tdealends = line.substr(10, (line.length()-10));
			int dealends;
			
			dealends = DtFrmt(tdealends);

			string line2a, line2b, line2c, line2d, line2e, line2f, line2g, line2h, line2i ;			
			add >> line2a;
			while (line2a != "#")
			{	string destination, temp1, temp2, temp3, temp4;
				int fromdate, todate, HKD, quota;
				
				add >> line2b >> line2c >> line2d >> line2e >> line2f >> line2g >> line2h >> line2i;
				destination = line2a.substr(0,3);
				temp1=line2a.substr(4,4);
				temp2=line2b;
				temp3=line2c;
				temp4=(temp1+" "+temp2+" "+temp3);
				
				fromdate=DtFrmt(temp4);
				
				temp1=line2e;
				temp2=line2f;
				temp3=line2g.substr(0,(line2g.length()-4));
				temp4=(temp1+ " "+temp2+" "+temp3);
				todate=DtFrmt(temp4);
				temp1=line2h.substr(0,(line2h.length()-6));
				stringstream xyz;
				xyz << temp1;
				xyz >> HKD;
				stringstream abc;
				abc << line2i;
				abc >> quota;
				add >> line2a;
				
				bool flg=true;
				for(int j=0; j<i; j++)
				{	if (plist[j].dest==destination && plist[j].ai==airline && plist[j].fromd==fromdate && plist[j].tod==todate && plist[j].dends==dealends &&plist[j].price==HKD)
					{	
						plist[j].quotal= (plist[j].quotal + quota);
						flg = false;
					}
				}
				if(flg)
					{
						plist[i].dest=destination;
						plist[i].ai=airline;
						
						plist[i].fromd=fromdate;
						plist[i].tod=todate;
						plist[i].dends=dealends;
						plist[i].price=HKD;
						plist[i].quotal=quota;
						i++;
						
					}
						
			}
		}
	}						
}

int DtFrmt(string date)
{	
	string tyyyy, tmmm, tdd, tdate;
	tyyyy = date.substr(0, 4);
	tmmm = date.substr(5, 3);
	tdd = date.substr(9, (date.length()-9));

	if (tmmm == "Jan")
		tmmm = "01";
	else if (tmmm == "Feb")
		tmmm = "02";
	else if (tmmm == "Mar")
		tmmm = "03";
	else if (tmmm == "Apr")
		tmmm = "04";
	else if (tmmm == "May")
		tmmm = "05";
	else if (tmmm == "Jun")
		tmmm = "06";
	else if (tmmm == "Jul")
		tmmm = "07";
	else if (tmmm == "Aug")
		tmmm = "08";
	else if (tmmm == "Sep")
		tmmm = "09";
	else if (tmmm == "Oct")
		tmmm = "10";
	else if (tmmm == "Nov")
		tmmm = "11";
	else if (tmmm == "Dec")
		tmmm = "12";
	

	if (tdd.length() < 2)
		tdate = (tyyyy+tmmm+"0"+tdd);
	else
		tdate = (tyyyy+tmmm+tdd);

	stringstream temp;
	temp << tdate;
	int DT;
	temp >> DT;

	return DT;


}
void command_clear(travel_promo plist[], int &kc, int i)
{
	for (int j=0; j; j++)
	{
		plist[j].search=0;	
	}

	kc=0;	

}
void command_today(travel_promo plist[], int &i)
{	int yyyymmdd;
	cin >> yyyymmdd;
	int counter=0;

	for (int j=0; j<i; j++)
	{	if (plist[j].dends > yyyymmdd)
		{	counter++;
			for (int k = counter-1; k<counter; k++)
			{	plist[k].dest=plist[j].dest;
				plist[k].ai=plist[j].ai;
				plist[k].fromd=plist[j].fromd;
				plist[k].tod=plist[j].tod;
				plist[k].price=plist[j].price;
				plist[k].dends=plist[j].dends;
				plist[k].quotal=plist[j].quotal;
				plist[k].search=plist[j].search;
			}				
		}
		
	}
	i=counter;
	

}
void command_preferai(travel_promo plist[], int i)
{	string xxx, dummy;
	int x=0;
	cin >> dummy;
	cin >> xxx;

	for (int j=0; j<i; j++)
	{	if (plist[j].search!=0)
		{	plist[j].search=0;
			if(plist[j].ai == xxx)
			{	x++;
				for (int k=x-1; k<x; k++)
				{	cout << "<" << k+1 << ">" << plist[j].dest << "-" << plist[j].ai << "-" << plist[j].fromd<< "-";
					cout << plist[j].tod << "-" << "HKD" << " " << plist[j].price << "," << " promotion expires ";
					cout << plist[j].dends << ", " << plist[j].quotal << " " << "quota" << endl;
					plist[j].search=k+1;
				}	
			}	
		}
	}		
}
void command_noai(travel_promo plist[], int i)
{	string xxx, dummy;
	int x=0;
	cin >> dummy;
	cin >> xxx;

	for (int j=0; j<i; j++)
	{	if (plist[j].search!=0)
		{	plist[j].search=0;
			if(plist[j].ai != xxx)
			{	x++;
				for (int k=x-1; k<x; k++)
				{	cout << "<" << k+1 << ">" << plist[j].dest << "-" << plist[j].ai << "-" << plist[j].fromd<< "-";
					cout << plist[j].tod << "-" << "HKD" << " " << plist[j].price << "," << " promotion expires ";
					cout << plist[j].dends << ", " << plist[j].quotal << " " << "quota" << endl;
					plist[j].search=k+1;
				}	
			}	
		}
	}		
}

void command_most(travel_promo plist[], int i, code_country clist[], int &c )
{	

	ofstream mst;
	mst.open("most.txt");


	int revenue=0; string mc;
	int tk=0; 
	for (int j=0; j<c; j++)
	{	int tk1=0;
		tk1=clist[j].tickets;
		for (int k=j+1; k<c; k++)
		{	if (clist[k].country==clist[j].country)
			{	
				tk1=tk1+clist[k].tickets;
			}	
		}
		if (tk1>=tk)
			tk=tk1;
	}
	for (int j=0; j<c; j++)
	{	int tk1=0;
		tk1=clist[j].tickets;
		for (int k=j+1; k<c; k++)
		{	if (clist[k].country==clist[j].country)
			{	
				tk1=tk1+clist[k].tickets;
				if (tk1 == tk)
					mc=clist[j].country;
			}	
		}
		
	}	
	for (int j=0; j<c; j++)
	{	if(clist[j].country==mc)
			revenue=revenue+clist[j].revenue;
	}	

	mst << mc << endl;
	mst << "#" << tk << endl;
	mst << "$" << revenue << endl;

	mst.close();

}

int main()
{
	travel_promo plist[500]={};
	code_country clist[200]={};
	int c=0;
	
	
	
	int kc=0;
	ifstream DB;
	ofstream IDB;
	int i=0;
	

	DB.open("iDB.txt");
	if (DB.fail())
	{	DB.open("mainDB.csv");
		if (DB.fail())
		{	cout << "error opening file" << endl;
			exit(1);
		}	
	}	


	readDataP (plist, DB, i);

	ifstream acode;
		acode.open("airportcode.txt");
		if (acode.fail())
			cout << "error opening airportcode.txt" <<endl;
		
		while(acode.good())
		{	string cd,cntry;
			getline(acode, cd  ,',');
			getline(acode, cntry);
			clist[c].code = cd;
			clist[c].country = cntry;
			c++;
		}
		acode.close();
		ifstream ID2R;
		ID2R.open("ID2.txt");
		while(ID2R.good())
		{	string temp1,temp2,temp4;
			getline(ID2R,temp1,'-');
			getline(ID2R,temp2,'-');
			getline(ID2R,temp4);
			int temp3,temp5;
			stringstream temp;
			temp << temp2;
			temp >> temp3;
			stringstream t;
			t << temp4;
			t >> temp5;
			for (int j=0; j<c; j++)
			{	if(clist[j].code==temp1)
				{	clist[j].revenue=temp3;
					clist[j].tickets=temp5;
				}	
			}		

		}
		ID2R.close();


	IDB.open("iDB.txt");
	string command;
	cin >> command; 
	while (command != "end")
	{	
		for (int j= 0; j<i; j++)	
		{	if (plist[j].quotal==0)
			{	for (int k=j; k<i; k++)
					{plist[k]=plist[k+1];}

				i--;	
			}
		}	

		if (command=="all")
			command_all(plist,i);

		else if (command == "buy")
			command_buy(plist, i, kc, clist,c);

		else if (command == "search")
			command_search(plist, i, kc);
		else if (command ==  "add")
			command_addpromo(plist,i);
		else if (command == "clear")
			command_clear(plist,kc, i);
		else if (command == "today")
			command_today(plist, i);
		else if (command == "prefer")
			command_preferai(plist, i);
		else if (command == "no")
			command_noai(plist, i);
		else if (command == "most")
			command_most(plist, i, clist,c);


		

		
		for (int j=0; j<i; j++)
		{	IDB << plist[j].dest << "," << plist[j].ai << "," << plist[j].fromd << "," << plist[j].tod << ",";
			IDB << plist[j].price << ","<< plist[j].dends << "," << plist[j].quotal<< endl;
		}	
		IDB.close()	;	
		cin >> command;	
	}	
	ofstream ID2;
	ID2.open("ID2.txt");
	for (int i=0; i < c; i++)
	ID2 << clist[i].code << "-" << clist[i].revenue << "-" << clist[i].tickets <<endl;
	ID2.close();	
	
	DB.close();
	
	return 0;	

}