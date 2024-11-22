#include "Neural.h"
#include <assert.h>
#include "Utils.h"

NeuronGene CrossOverNeuron(NeuronGene* a, NeuronGene* b)
{
    assert(a->neuron_id == b->neuron_id);
    NeuronGene new_neuro;
    new_neuro.neuron_id = a->neuron_id;
    new_neuro.bias = rngChooseDouble(0.5, a->bias, b->bias);

    return new_neuro;
}

LinkGene CrossOverLink(LinkGene* a, LinkGene* b)
{
    assert(a->link_id.input_id == b->link_id.input_id && a->link_id.output_id == b->link_id.output_id);
    LinkGene new_link;
    new_link.link_id = a->link_id;
    new_link.weight = rngChooseDouble(0.5, a->weight, b->weight);
    new_link.isEnabled = rngChooseBool(0.5, a->isEnabled, b->isEnabled);

    return new_link;
}

Genome CrossOver(Individual* dominant, Individual* recessive)
{
    
}
