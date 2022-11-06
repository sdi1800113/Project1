Project1 Πολυγωνοποίηση σημειοσυνόλου με τη χρήση της βιβλιοθήκης CGAL


Δήμα Φωτεινή 1115201800041
Μαυράκη Μαρία 1115201800113



Tο πρόγραμμα είναι στο αρχείο ergasia.cpp .

Kατάλογος των αρχείων κώδικα / επικεφαλίδων και περιγραφή τους: 
 
sortcolADesc -> συνάρτηση που ταξινομεί τα σημεία κατά Χ se descending order
sortcolBDesc -> συνάρτηση που ταξινομεί τα σημεία κατά Y se descending order
sortcolAAsc -> συνάρτηση που ταξινομεί τα σημεία κατά Χ se ascending order
sortcolBAsc -> συνάρτηση που ταξινομεί τα σημεία κατά Y se ascending order
void split(const std::string &s, char delim, std::vector<std::string> &elems) -> διαβάζει μια γραμμή και τη χωρίζει σε tokens
template <class InputIterator, class OutputIterator, class Traits> OutputIterator ch_graham_anderson -> graham anderson (σύμφωνα με documentation)

Στην main εκτελούνται όλη η υπόλοιπή λογική του κώδικα.
Τα βήματα είναι τα εξής :

1. Ελεγχος εάν υπάρχει ορισμένη η τιμή input file (-i) (εάν όχι exit)
2. Διάβασμα του αρχείου line by line
3. split line, create Points
4. Ελεγχος εάν υπάρχει ορισμένη η τιμή output file (-o) (εάν όχι exit)
5. Ελεγχος εάν υπάρχει ορισμένη η τιμή algorithm (-algorith) (εάν όχι exit)
6. Υπάρχουν δύο επιλογές:
6α. incremental
	1. sortarisma ανάλογα
	2. edge selection
	3. write to output file
6b. convex hull
	1. 2 δημιουργία ΚΠ
	2. εύρεση ορατής ακμής, επιλογή ορατής ακμής και επέκταση της Α ώστε να περιλάβει το σημείο
	3. write to output file

Εγκατάσταση cgal στα linux σύμφωνα με τις διαφάνειες 
Οδηγίες μεταγλώττισης του προγράμματος (στον ίδιο φάκελο) :

 git clone https://github.com/CGAL/cgal.git 
 ./cgal.git/Scripts/scripts/cgal_create_cmake_script
 mkdir -p build/debug
 cd build/debug
 cmake -DCMAKE_BUILD_TYPE=Debug -DCGAL_DIR:PATH=/path/to/cgal.git ../..
 make ergasia.cpp

