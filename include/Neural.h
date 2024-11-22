#ifndef NEURAL_H_
#define NEURAL_H_

#include <stdbool.h>

typedef struct
{
    int neuron_id;
    double bias;
} NeuronGene;

typedef struct
{
    int input_id;
    int output_id;
} LinkID;

typedef struct
{
    LinkID link_id;
    double weight;
    bool isEnabled;
} LinkGene;

typedef struct
{
    int genome_id;
    int num_inputs;
    int num_outputs;
    NeuronGene* neurons;
    LinkGene* linkGenes;
} Genome;

typedef struct
{
    Genome genome;
    double fitness;
} Individual;

NeuronGene CrossOverNeuron(NeuronGene* a, NeuronGene* b);
LinkGene CrossOverLink(LinkGene* a, LinkGene* b);

Genome CrossOver(Individual* dominant, Individual* recessive);

#endif
