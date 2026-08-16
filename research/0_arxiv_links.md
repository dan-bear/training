
---
title: **Nemotron-Labs-3-Puzzle-75B-A9B: Compressing Hybrid MoE LLMs**
- link: https://arxiv.org/html/2607.04371v1
- authors: nvidia
- tag:
    - inference
    - model compression
- terminologies:
    - Iterative Puzzle compression framework.
    - pruning (compression technique)
    - knowledge distillation (compression technique)
    - reinforcement learning
    - quantization (compression technique)
    - multi-token predication head
    - heterogeneous MoE pruning (compression technique)
        - MoE - Mixture of Experts -  
    - active parameter budget
    - mamba pruning - state-space-models (SSM)
 - principles/results/claims:
    - large hybrid MoE models can be optimized for deployment efficiency while maintaining downstream capability.
    - requests with long inputs are typically compute bound - FLOP/s (prefill)
    - requests with long outputs are typically IO bound - GB/s (decode streaming weights repeatedly).
    - ultra-long-context requests are typically restricted by device memory - GB (KV cache residency)
   

---
