#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  int constructionspots;
  int *buildingheights;
  string **skyline;
  string curr;

  input >> constructionspots;
  getline(input, curr); //consume the newline character for the first line.
  skyline = new string*[constructionspots];

  //you will need to keep track of the height of each building
  buildingheights = new int[constructionspots];

  for (int i = 0; i < constructionspots; i++) {
	  buildingheights[i] = 0;
	  skyline[i] = NULL;
  }

  while(getline(input, curr)) {
	  stringstream ss;
	  ss << curr;
	  ss >> curr;
	  if (curr == "BUILD") {
		  int x,y;
		  string c;
		  ss >> x;
		  ss >> y;
		  ss >> c;
		  if (ss.fail() || skyline[x] != NULL) {
			  output << "Error - incorrect command" << endl;
		  }
		  else {
		  	if (x < constructionspots && x >=0) //See if its a legal spot and within scope
		  	{
		  		if (y > 0)
		  		{
		  			buildingheights[x] = y;
		  			skyline[x] = new string[y];
		  			for (int i = 0; i < y; i++)
		  			{
		  				skyline [x][i] = c;
		  			}
		  		}
		  		else
		  		{
		  			output << "Error - building height should be more than 0!" << endl;
		  		}
		  	}
		  	else
		  	{
		  		output << "Error - Not a construction spot!" << endl;
		  	}

		  }
	  }
	  else if (curr == "EXTEND") {
	  	int x,y;
		  string c;
		  ss >> x;
		  ss >> y;
		  ss >> c;
		  if (ss.fail() || skyline[x] == NULL) {
			  output << "Error - incorrect command" << endl;
		  }
		  else
		  {
		  	int oldheight = buildingheights[x];
		  	buildingheights[x] = y + oldheight;
		  	y = buildingheights[x];
		  	string* buffer = new string[y];
		  	for (int i = 0; i < oldheight; ++i)
		  		{
		  			buffer[i] = skyline[x][i];
		  		}	

		  		delete [] skyline[x];

		  	skyline[x] = new string[y];
		  	for (int i = 0; i < oldheight; ++i)
		  		{
		  			skyline[x][i] = buffer[i];
		  		}
			for (int i = oldheight; i < y; ++i)
	  			{
		  			skyline[x][i] = c;
		  		}
		  		delete [] buffer;
		   }
	  }
	  else if (curr == "DEMOLISH") {
	  	int x;
	  	ss >> x;
	  	if (ss.fail() || skyline[x] == NULL)
	  	{
	  		output << "Error : building doesnt exist at " << x << "so cannot demolish!" << endl;
	  	}
	  	else
	  	{
	  		delete [] skyline[x];
	  		skyline [x] = NULL;
	  		buildingheights[x] = 0;
	  	}
	  }
	  else if (curr == "SKYLINE") {
	  	int y;
	  	ss >> y;
	  	for (int i = 0; i < constructionspots; ++i)
	  	{
	  		if (buildingheights[i] < y)
	  		{
	  			output << "SKY ";
	  		}
	  		else
	  		{
	  			output << skyline[i][y-1] << " ";
	  		}
	  	}
	  	output << endl;
	  }
	  else {
	  }
  }
  for (int i = 0; i < constructionspots ; ++i)
	  {
	    delete [] skyline[i];
	  }
	delete [] skyline;
	delete [] buildingheights;
  return 0;
}
