#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <vector>

#include <CGAL/ch_graham_andrew.h>
#include <algorithm>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef std::vector<Point_2> Points;

using namespace std;


//For comparing 1'st column order
bool sortcolADesc(const vector<int>& v1,const vector<int>& v2) { 
     return v1[0] < v2[0]; 
} 

//For comparing 2'nd column order
bool sortcolBDesc(const vector<int>& v1,const vector<int>& v2) { 
     return v1[1] < v2[1]; 
} 

//For comparing 1'st column order
bool sortcolAAsc(const vector<int>& v1,const vector<int>& v2) { 
     return v1[0] > v2[0]; 
} 

//For comparing 2'nd column order
bool sortcolBAsc(const vector<int>& v1,const vector<int>& v2) { 
     return v1[1] > v2[1]; 
} 

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_graham_anderson( InputIterator  first, InputIterator  beyond,
                    OutputIterator result, const Traits&  ch_traits)
{
  using namespace boost;
  typedef typename Traits::Point_2            Point_2;
  typedef typename Traits::Less_xy_2          Less_xy_2;
  typedef typename Traits::Less_rotate_ccw_2  Less_rotate_ccw_2;
  if (first == beyond) return result;
  std::vector< Point_2 >  V (first, beyond);
  typename std::vector< Point_2 >::iterator it =
               std::min_element(V.begin(), V.end(), Less_xy_2());
  const Point_2 p = *it;
  std::sort( V.begin(), V.end(), [&p](const Point_2& p1, const Point_2& p2){return Less_rotate_ccw_2()(p, p1, p2);} );
  if ( *(V.begin()) != *(V.rbegin()) )
  {
    result = CGAL::ch_graham_andrew_scan( V.begin(), V.end(), result, ch_traits);
  }
  // add the last point of the sequence that is
  // not added by ch_graham_andrew_scan
  *result++ = *(V.rbegin());
  return result;
}

class InputParser{
    public:
        InputParser (int &argc, char **argv){
            for (int i=1; i < argc; ++i)
                this->tokens.push_back(std::string(argv[i]));
        }
        /// @author iain
        const std::string& getCmdOption(const std::string &option) const{
            std::vector<std::string>::const_iterator itr;
            itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
        }
        /// @author iain
        bool cmdOptionExists(const std::string &option) const{
            return std::find(this->tokens.begin(), this->tokens.end(), option)
                   != this->tokens.end();
        }
    private:
        std::vector <std::string> tokens;
};

template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_graham_anderson( InputIterator  first, InputIterator  beyond,
                    OutputIterator result, const Traits&  ch_traits)
{
  typedef typename Traits::Point_2            Point_2;
  typedef typename Traits::Less_xy_2          Less_xy_2;
  typedef typename Traits::Less_rotate_ccw_2  Less_rotate_ccw_2;

  if (first == beyond) return result;
  std::vector< Point_2 >  V (first, beyond);
  typename std::vector< Point_2 >::iterator it =
               std::min_element(V.begin(), V.end(), Less_xy_2());
  const Point_2 p = *it;
  std::sort( V.begin(), V.end(), [&p](const Point_2& p1, const Point_2& p2){return Less_rotate_ccw_2()(p, p1, p2);} );
  if ( *(V.begin()) != *(V.rbegin()) )
  {
    result = CGAL::ch_graham_andrew_scan( V.begin(), V.end(), result, ch_traits);
  }
  // add the last point of the sequence that is
  // not added by ch_graham_andrew_scan
  *result++ = *(V.rbegin());
  return result;

}


int main() {
    std::ifstream infile ("euro-night-0000010.instance");
    std::string line;
    Points points, result;
	// arg -i
	//read file
    InputParser input(argc, argv);
    if(input.cmdOptionExists("-i")){
        // get input file
		const std::string &filename = input.getCmdOption("-i");
		if (!filename.empty()){
			
			// To παρακάτω snippet κώδικα
			// δημιουργήθηκε λόγω ότι αρχεία instance δεν υποστηρίζονται
			// https://doc.cgal.org/latest/Stream_support/IOStreamSupportedFileFormats.html
			// Do interesting things ...
			std::ifstream infile (filename);
			//read all lines ignore empy lines and lines starting with #
			while (std::getline(infile, line))
			{
				vector<string> row_values;
				//ignore lines that start with #
				if (line.empty() || line.rfind(line, 0) == 0){
					//ignore
				}
				else
				{
					split(line, '\t', row_values);
					points.push_back(Point_2(row_values[1],row_values[2]));
					
				}

				cout << endl;
			 }
			 
			cout << "read file completeted" << endl;
		}
		else
		{
			//exit
			return 0;
		}
		
    }


    // arg -o
    if(input.cmdOptionExists("-o")){
		//generate output file
	}
	else
	{
		return 0;
	}
	
	// arg -algorithm
    if(input.cmdOptionExists("-algorithm")){
		const std::string &algorithm = input.getCmdOption("-algorithm");
		//incremental
		if (line.rfind("incremental"), 0) == 0){
			//-initialization
			if(input.cmdOptionExists("-initialization")){
				const std::string &sort = input.getCmdOption("-algorithm");
				switch (day) 
				{
				  case 1:
					//do nothinf
					break;
				  case 2:
					//Sort points based on x Desc
					sort(points.begin(), points.end(),sortcolADesc());
					break;
				  case 3:
					//Sort points based on y Desc
					sort(points.begin(), points.end(),sortcolBDesc());
					break;
				  case 4:
					//Sort points based on x Asc
					sort(points.begin(), points.end(),sortcolAAsc())
					break;
				  case 5:
					//Sort points based on y Asc
					sort(points.begin(), points.end(),sortcolBAsc());
					break;
				  
				  default:
					
					break;
				}
				
				
			}
			//-edge_selection
			if(input.cmdOptionExists("-edge_selection")){
				//περίπτωση 1
				//περίπτωση 2
				//περίπτωση 3
				std::istream_iterator< Point_2 >  in_start( points );
				std::istream_iterator< Point_2 >  in_end;
				std::ostream_iterator< Point_2 >  out( std::cout, "\n" );
				ch_graham_anderson(in_start, in_end, out, K());
				//output
				for( std::size_t i : out){
					std::cout << "points[" << i << "] = " << points[i] << std::endl;
				}
				
			}
			
			//write to output file
			if(input.cmdOptionExists("-o")){
				if(!CGAL::IO::write_points(input.getCmdOption("-o"), points)){
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
		
	
		
		//convex_hull
		if (line.rfind("convex_hull"), 0) == 0){			
			// υπολογισμός ΚΠ
	        // ΜΕ ΒΑΣΗ ΤΟ ΚΠ. (α) Υπολογισμός ΚΠ και αρχικοποίηση της πολυγωνικής γραμμής Α. (β). Για κάθε εσωτερικό
			// σημείο, εύρεση ορατής ακμής, επιλογή ορατής ακμής και επέκταση της Α ώστε να περιλάβει το σημείο.
			CGAL::convex_hull_2( points.begin(), points.end(), std::back_inserter(result) );
			
			std::cout << result.size() << " points on the convex hull" << std::endl;  std::vector<std::size_t> indices(points.size()), out;
			std::iota(indices.begin(), indices.end(),0);
			CGAL::convex_hull_2(indices.begin(), indices.end(), std::back_inserter(out),
							  Convex_hull_traits_2(CGAL::make_property_map(points)));
			//output
			for( std::size_t i : out){
				std::cout << "points[" << i << "] = " << points[i] << std::endl;
			}
			
			//write to output file
			if(input.cmdOptionExists("-o")){
				if(!CGAL::IO::write_points(input.getCmdOption("-o"), points)){
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
			
		
		
	}
	else
	{
		return 0;
	}
	
   


    
	
	
	
	
    
	
	
	
    return 0;
}