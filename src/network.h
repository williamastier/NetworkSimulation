#ifndef NETWORK
#define NETWORK

#include <map>
#include <vector>
#include <iostream>

/*!
 * This is a network of nodes with bidirectional links: if <b>(a, b)</b> is a link then <b>(b, a)</b> is also a link.
 * Each node supports a *double* value, and the list of nodes is in fact defined by the list of their values.
 */

class Network {

public:
    Network() {}

    /*!
     * @brief Resizes the list of nodes (\ref values) and also resets all values.
     * After this function is called \ref values has size *t* and
     * contains random numbers (normal distribution, mean=0, sd=1).
     */
    void resize(const size_t & t);

    /*!
     * @brief Adds a bidirectional link between two nodes
     *
     * @param[in] a,b the indexes if the two nodes
     *
     * @param[out] success the link was succesfully inserted
     * (true if both nodes exist and the link did not exist yet)
     */
    bool add_link(const size_t & a, const size_t & b);

    /*!
     * @brief : Creates random connections between nodes: each node *n* will be linked with *degree(n)* other nodes
     * (randomly chosen) where *degree(n)* is Poisson-distributed.
     * All previous links are cleared first.
     *
     * @param mean_deg the average of the Poisson distribution.
     */
    size_t random_connect(const double &);

    /*!
     * @brief Resets all node values.
     *
     * @param[in] vector of new node values
     * @param[out] number of nodes successfully reset
     */
    size_t set_values(const std::vector<double>&);

    /*!
     * @brief Number of nodes
     */
    size_t size() const;

    /*!
     * @brief Degree (number of links) of node no *n*
     */
    size_t degree(const size_t &_n) const;

    /*!
     * @brief Value of node no *n*
     */
    double value(const size_t &_n) const;

    /*!
     * @brief All node values in descending order
     *
     * @return a vector<double> of the Network::values in descending order
     */
    std::vector<double> sorted_values() const;

    /*!
     * @brief All neighbors (linked) nodes of node no *n*
     */
    std::vector<size_t> neighbors(const size_t&) const;

private:
    std::vector <double> values;
    std::multimap <size_t, size_t> links;

};

#endif