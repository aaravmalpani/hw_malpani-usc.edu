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
		  float f,k;
		  string c;
		  ss >> f;
		  ss >> k;
		  ss >> c;
		  if (f - int(f) != 0)
	  	{
	  		output << "Error : You can only input int values" << endl;
	  	}
	  	else if (k - int(k) != 0)
	  	{
	  		output << "Error : You can only input int values" << endl;
	  	}

	  	else{
	  		int x = int(f);
	  		int y = int(k);

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
	  }
	  else if (curr == "EXTEND") {
	  	float f,k;
		  string c;
		  ss >> f;
		  ss >> k;
		  ss >> c;
		  if (f - int(f) != 0)
	  	{
	  		output << "Error : You can only input int values" << endl;
	  	}
	  	else if (k - int(k) != 0)
	  	{
	  		output << "Error : You can only input int values" << endl;
	  	}

	  	else{
	  		int x = int(f);
	  		int y = int(k);

		  if (ss.fail() || skyline[x] == NULL) {
			  output << "Error - incorrect command/Building doesnt exist" << endl;
		  }
		  else if (x>=constructionspots || x<0)
		  {
		  	output << "Error - not a construction spot" << endl;
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
	  }
	  else if (curr == "DEMOLISH") {
	  	float f;
	  	ss >> f;
	  	if (f - int(f) != 0)
	  	{
	  		output << "Error : You can only input int values" << endl;
	  	}
	  	else{
	  		int x = int(f);
	  	if (ss.fail() || skyline[x] == NULL)
	  	{
	  		output << "Error : building doesnt exist at " << x << " so cannot demolish!" << endl;
	  	}
	  	else if (x>=constructionspots || x<0)
		  {
		  	output << "Error - cannot delete this spot" << endl;
		  }
	  	else
	  	{
	  		delete [] skyline[x];
	  		skyline [x] = NULL;
	  		buildingheights[x] = 0;
	  	}
	  }
	  }
	  else if (curr == "SKYLINE") {
	  	float f;
	  	ss >> f;
	  	if (f - int(f) != 0)
	  	{
	  		output << "Error : You can only input int values" << endl;
	  	}
	  	else{
	  		int y = int(f);
	  		
	  	if (y == 0)
	  	{
	  		output << "Cannot print floor 0" << endl;
	  	}
	  	else
	  	{
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
	  }
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
