#include "network.h"
#include "random.h"

void Network::resize (const size_t & t) {
    // On ne garde que les t premières cases de values
    values.resize(t);

    // Chaque valeur a alors une valeurs aléatoire (issue d'une distribution normale)
    RNG.normal(values);
}

bool Network::add_link(const size_t & node_a, const size_t & node_b) {

    // Si les deux nodes sont identiques
    if (node_a == node_b) {
        // Alors il est impossible de faire un lien entre eux
        return false;
    }

    // Sinon, si un des noeuds n'a pas de valeur
    else if(node_a >= values.size() or (node_b >= values.size())) {
        // Alors il est également impossible de faire un lien entre eux
        return false;
    }

    // Sinon, on regarde dans les links
    else {

        for (std::multimap<size_t, size_t>::iterator it = links.begin(); it != links.end(); ++it) {

            // Si le lien entre node_a et node_b existe déjà
            if ((it->first == node_a and it->second == node_b) or (it->first == node_b and it->second == node_a)) {
                // Alors il est impossible de créer une nouvelle fois le même lien
                return false;
            }
        }
    }

    // Si on arrive à ce stade, alors les conditions pour créer un lien sont bonnes

    // On crée un lien de node_a à node_b et aussi de node_b à node_a
    links.insert(std::make_pair(node_a , node_b));
    links.insert(std::make_pair(node_b , node_a));

    // On indique que le lien a bien pu être créé
    return true;
}

size_t Network::random_connect( const double & average_number_of_links) {
    // On efface tous les liens déjà créés
    links.clear();

    size_t number_of_links (0);

    // On crée un vecteur avec les noms des noeuds
    std::vector<size_t> nodes;

    // On crée un vecteur avec le nombre de liens pour chaque noeud
    std::vector<int> poissons(size());

    for(size_t node=0; node < size() ; node++) {
        nodes.push_back(node);
    }

    // On affecte à chaque nombre de lien un nombre issu d'une distribution aléatoire
    RNG.poisson(poissons, average_number_of_links);

    for(size_t node=0; node < size() ; node++) {

        // On réarrange les noeuds aléatoirement (donc les valeurs qui leur sont associées changent)
        RNG.shuffle(nodes);

        size_t new_links(0);

        // On crée des connexions après avoir vérifié qu'un noeud n'ait pas plus de connexions
        // qu'il doit avoir et qu'il n'ait pas plus de liens que de noeuds existants
        for(int i(0); new_links < poissons[node] and i < size() ; ++i) {

            // Si on peut créer un lien avec le noeud i
            if (add_link(node, nodes[i])) {
                // Alors on crée le lien et on incrémente le compteur de nouveaux liens du noeud en question
                ++new_links;
            }
        }

        // On incrémente le nombre total de nouveaux liens créés
        number_of_links += new_links;
    }
    return number_of_links;
}

size_t Network::set_values(const std::vector<double> & new_values ) {
    size_t number_of_values(0);

    for(size_t node=0; (node < values.size()) and (node < new_values.size()) ; node++) {
        values[node] = new_values[node];
        ++number_of_values;
    }
}

size_t Network::size() const {
    return values.size();
}

size_t Network::degree(const size_t & _n) const {
    try {
        return links.count(_n); // On retourne le nombre de lien correspondant au noeud _n
    } catch (std::out_of_range & e) {
        std::cout << "This Network has not got any link starting from " << _n  << " as " << _n << " is not a node."<< std::endl;
    }
}

double Network::value(const size_t & _n) const {
    try {
        return values[_n];
    } catch (std::out_of_range & e){
        std::cout << "The node " << "_n" << "does not exists so it has not got any value" << std::endl;
    }
}

std::vector<double>  Network::sorted_values() const {
    // On crée un vecteur de valeurs décroissantes initialisé à values
    std::vector<double> descending_values = values;

    // On trie le vecteur dans l'orde décroissant
    sort(descending_values.begin() , descending_values.end() , std::greater<double>());

    return descending_values;
}

std::vector<size_t> Network::neighbors(const size_t & key) const {
    // On crée un vecteur de neighbors
    std::vector<size_t> neighb;

    for (std::multimap<size_t,size_t>::const_iterator i =links.begin(); i < links.end(); ++i) {
        if (i->first == key) {
            //Dès qu'on a la bonne clé, on ajoute les liens de key à neighb
            neighb.push_back(i->second);
        }
    }
    return neighb;
}