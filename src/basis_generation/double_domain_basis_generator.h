#ifndef DOUBLEDOMAINBASISGENERATOR_H
#define DOUBLEDOMAINBASISGENERATOR_H
#include <vector>
#include <functional>
#include "subspace_tet.h"
#include "single_domain_basis_generator.h"
#include "basis_generator.h"


class DoubleDomainBasisGenerator
{
public:
  DoubleDomainBasisGenerator(const char *mesh_file_uncons, const char *mesh_file_cons, AffineTransformer<double>* transformer = NULL);
  void ProcessFixedVertex(const char *filename);
  void GenerateBasis(const char *basis_prefix, int linear_basis_num, int final_basis_num);
    /*
  void GenerateBasis(const char *basis_prefix, int linear_basis_num, int final_basis_num);
  void RegenerateStitchBasis(int modeID);
  void preLoad(const char* prefix);
  void setStitchedStiffnessMatrix(SparseMatrix* spmat);
  void SetFixedVertex(std::function<bool (int, double *)> IsFixed);
  void SetFixedVertex(std::vector<int> fixed_verts);
  void ProcessFixedVertex(const char *filename);

  void setStiffyMult(int s) { basis_generator->setStiffyMultiplier(s);}



  /// select the $fixed_vert_num_per_domain$ number vertex that are closest to
  /// the center of mass for each partition as fixed vertices
  void SetFixedVertex(int fixed_vert_num);
  virtual ~SingleDomainBasisGenerator();
  std::vector<int> fixed_verts_;
  char file_name_[1024];

  BasisGenerator *basis_generator;*/

  SingleDomainBasisGenerator *constrained_portion_;
  SingleDomainBasisGenerator *unconstrained_portion_;

  std::vector<double> linearModes_;
  std::vector<double> eigenValues_;
  std::vector<double> eigenVectors_;
  std::vector<double> frequencies_;
};

#endif // SINGLEDOMAINBASISGENERATOR_H
