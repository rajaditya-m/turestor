#include <queue>
#include <utility>
#include <set>
#include "tet.h"
#include "StVKHessianTensor.h"
#include "vector_io.h"
#include "vector_lib.h"
#include "tet_mesh_simulator_bridge.h"
#include "print_macro.h"
#include "string_formatter.h"
#include "basis_io.h"
#include "global.h"
#include "basis_generator.h"
#include "double_domain_basis_generator.h"
#include "sparseMatrix.h"

#define ELT(numRows,i,j) (((long)j)*((long)numRows)+((long)i))

#define COLMAJORIDX

DoubleDomainBasisGenerator::DoubleDomainBasisGenerator(const char *mesh_file_uncons, const char *mesh_file_cons, AffineTransformer<double> *transformer)
{
    unconstrained_portion_ = new SingleDomainBasisGenerator(mesh_file_uncons,transformer,false);
    constrained_portion_ = new SingleDomainBasisGenerator(mesh_file_cons,transformer,false);
}

void DoubleDomainBasisGenerator::ProcessFixedVertex(const char* filename){
    constrained_portion_->ProcessFixedVertex(filename);
}

void DoubleDomainBasisGenerator::GenerateBasis(const char *basis_prefix, int linear_basis_num, int final_basis_num){
    constrained_portion_->GenerateBasis(basis_prefix,linear_basis_num/2,final_basis_num/2,false);
		unconstrained_portion_->GenerateBasis(basis_prefix,linear_basis_num/2,final_basis_num/2,false);


    //Now we will generate the missing pieces and piece them together
    //First the non-linear modes if you please
    int unconsVertNum = unconstrained_portion_->vertex_num_;
    int consVertNum = constrained_portion_->vertex_num_;
    int totalVerts = unconsVertNum+consVertNum;
		int n3 = totalVerts * 3;
    nonLinearModes_.resize(totalVerts*3*final_basis_num,0);
		for (int c = 0; c<(final_basis_num / 2); c++){
        for(int r=0;r<consVertNum*3;r++){
					nonLinearModes_[ELT(totalVerts * 3, r, c)] = constrained_portion_->basis_generator->non_linear_modes_[ELT(consVertNum * 3, r, c)];
        }
    }
		for (int c = 0; c<(final_basis_num / 2); c++){
        for(int r=0;r<unconsVertNum*3;r++){
					nonLinearModes_[ELT(totalVerts * 3, r + (consVertNum * 3), c + (final_basis_num / 2))] = unconstrained_portion_->basis_generator->non_linear_modes_[ELT(unconsVertNum * 3, r, c)];
        }
    }
		sprintf(file_name_, "%s.basis.bin", basis_prefix);
		WriteBasisInBinary(file_name_, totalVerts, final_basis_num, &nonLinearModes_[0]);

		//Next we want the individual basises (youknow for cubature and stuff)
		std::vector<double> paddedBasis1(consVertNum * 3 * final_basis_num,0);
		memcpy(&paddedBasis1[0], &(constrained_portion_->basis_generator->non_linear_modes_[0]), sizeof(double)*consVertNum * 3 * (final_basis_num / 2));
		sprintf(file_name_, "%s.basis_1.bin", basis_prefix);
		WriteBasisInBinary(file_name_, consVertNum, final_basis_num, &paddedBasis1[0]);

		std::vector<double> paddedBasis2(unconsVertNum * 3 * final_basis_num, 0);
		memcpy(&paddedBasis2[unconsVertNum * 3 * (final_basis_num / 2)], &(unconstrained_portion_->basis_generator->non_linear_modes_[0]), sizeof(double)*unconsVertNum * 3 * (final_basis_num / 2));
		sprintf(file_name_, "%s.basis_2.bin", basis_prefix);
		WriteBasisInBinary(file_name_, unconsVertNum, final_basis_num, &paddedBasis2[0]);
		sprintf(file_name_, "%s.basis_2.txt", basis_prefix);
		WriteBasisInText(file_name_, unconsVertNum, final_basis_num, &paddedBasis2[0]);

		//Next we dump the non-linear weights
		sprintf(file_name_, "%s.nonlin_weights.bin", basis_prefix);
		nonLinWeights_.resize(final_basis_num, 0);
		std::copy(constrained_portion_->basis_generator->eigen_values_.begin(), constrained_portion_->basis_generator->eigen_values_.end(), nonLinWeights_.begin());
		std::copy(unconstrained_portion_->basis_generator->eigen_values_.begin(), unconstrained_portion_->basis_generator->eigen_values_.end(), nonLinWeights_.begin()+(final_basis_num/2));
		dj::Write1DVectorBinary(file_name_,nonLinWeights_);

		//Next we dump the pure eigen values 
		sprintf(file_name_, "%s.pure_eigen_vals.bin", basis_prefix);
		eigenValues_.resize(linear_basis_num, 0);
		std::copy(constrained_portion_->basis_generator->pure_eigen_values_.begin(), constrained_portion_->basis_generator->pure_eigen_values_.end(), eigenValues_.begin());
		std::copy(unconstrained_portion_->basis_generator->pure_eigen_values_.begin(), unconstrained_portion_->basis_generator->pure_eigen_values_.end(), eigenValues_.begin() + (linear_basis_num / 2));
		dj::Write1DVectorBinary(file_name_,eigenValues_);

		//Next we dump the pure eigen vectors
		eigenVectors_.resize(totalVerts * 3 * linear_basis_num, 0);
		for (int c = 0; c<(linear_basis_num / 2); c++){
			for (int r = 0; r<consVertNum * 3; r++){
				eigenVectors_[ELT(totalVerts * 3, r, c)] = constrained_portion_->basis_generator->pure_eigen_vectors_[ELT(consVertNum * 3, r, c)];
			}
		}
		for (int c = 0; c<(linear_basis_num / 2); c++){
			for (int r = 0; r<unconsVertNum * 3; r++){
				eigenVectors_[ELT(totalVerts * 3, r + (consVertNum * 3), c + (linear_basis_num / 2))] = unconstrained_portion_->basis_generator->pure_eigen_vectors_[ELT(unconsVertNum * 3, r, c)];
			}
		}
		sprintf(file_name_, "%s.pure_eigen_vecs.bin", basis_prefix);
		WriteBasisInBinary(file_name_, totalVerts, linear_basis_num, &eigenVectors_[0]);
		sprintf(file_name_, "%s.pure_eigen_vecs.txt", basis_prefix);
		WriteBasisInText(file_name_, totalVerts, linear_basis_num, &eigenVectors_[0]);

		//Finally we dump the frequencies also 
		sprintf(file_name_, "%s.lin_freqs.bin", basis_prefix);
		frequencies_.resize(linear_basis_num, 0);
		std::copy(constrained_portion_->basis_generator->frequencies_.begin(), constrained_portion_->basis_generator->frequencies_.end(), frequencies_.begin());
		std::copy(unconstrained_portion_->basis_generator->frequencies_.begin(), unconstrained_portion_->basis_generator->frequencies_.end(), frequencies_.begin() + (linear_basis_num / 2));
		dj::Write1DVectorBinary(file_name_, frequencies_);

		//Also we dump the hessians but this one will beslighlty   tricky 
		sprintf(file_name_, "%s.default_hessian_1.bin", basis_prefix);
		constrained_portion_->basis_generator->stVKStiffnessHessian->SaveHessianAtZeroToFile(file_name_);
		sprintf(file_name_, "%s.default_hessian_2_offset.bin", basis_prefix);
		unconstrained_portion_->basis_generator->stVKStiffnessHessian->SaveHessianAtZeroToFileWithOffset(file_name_,consVertNum);
		//unconstrained_portion_->basis_generator->stVKStiffnessHessian->AppendHessianAtZeroToFileWithOffset(file_name_,consVertNum);

		//Finally we dump the Original RHS Columns 
		int unconsRHSNum = unconstrained_portion_->basis_generator->numColsOriginalRHS_;
		int consRHSNum = constrained_portion_->basis_generator->numColsOriginalRHS_;
		int totalRHSNum = unconsRHSNum + consRHSNum;
		double* orgRHS = new double[n3 * totalRHSNum];
		memset(orgRHS,0,sizeof(double)*n3*totalRHSNum);
		for (int c = 0; c<consRHSNum; c++){
			for (int r = 0; r<consVertNum * 3; r++){
				orgRHS[ELT(n3,r,c)] = constrained_portion_->basis_generator->rhsOriginal_(r, c);
			}
		}
		for (int c = 0; c<unconsRHSNum; c++){
			for (int r = 0; r<unconsVertNum * 3; r++){
				orgRHS[ELT(n3,r + (consVertNum * 3), c + consRHSNum)] = unconstrained_portion_->basis_generator->rhsOriginal_(r, c);
			}
		}
		sprintf(file_name_, "%s.rhs_original.bin", basis_prefix);
		std::ofstream out(file_name_, std::ios::binary);
		out.write((char*)&n3, sizeof(int));
		out.write((char*)&totalRHSNum, sizeof(int));
		out.write((char*)orgRHS, sizeof(double) * n3 * totalRHSNum);
		out.close();


}

/*
void SingleDomainBasisGenerator::preLoad(const char *basis_prefix) {
    basis_generator = new BasisGenerator(inv_fem_->vega_mesh_, &mass_[0]);
    if (fixed_verts_.size() != 0) {
      basis_generator->SetFixedVertices(std::set<int>(fixed_verts_.begin(), fixed_verts_.end()));
    }
    basis_generator->SetInterfaceVertices(interface_vertices_,interface_vertex_split_);
    basis_generator->preLoad(basis_prefix);
    basis_generator->setPrefix(basis_prefix);

}

void SingleDomainBasisGenerator::GenerateBasis(const char *basis_prefix, int linear_basis_num, int final_basis_num) {
  basis_generator = new BasisGenerator(inv_fem_->vega_mesh_, &mass_[0]);
  int numRows = vertex_num_ * 3;
  int numRows1 = domain_offset_toggle_ * 3;
  int numRows2 = numRows - numRows1;
  if (fixed_verts_.size() != 0) {
    basis_generator->SetFixedVertices(std::set<int>(fixed_verts_.begin(), fixed_verts_.end()));
  }
  basis_generator->setPrefix(basis_prefix);
  basis_generator->SetInterfaceVertices(interface_vertices_,interface_vertex_split_);
  basis_generator->ComputeAllModes(linear_basis_num, final_basis_num);

  sprintf(file_name_, "%s.basis.bin", basis_prefix);
  WriteBasisInBinary(file_name_, vertex_num_, final_basis_num, &(basis_generator->non_linear_modes_[0]));

  sprintf(file_name_, "%s.basis.txt", basis_prefix);
  WriteBasisInText(file_name_, vertex_num_, final_basis_num, &(basis_generator->non_linear_modes_[0]));

  double *basis_split1 = new double[numRows1 * final_basis_num];
  for(int i = 0; i < numRows1; i++) {
      for(int j = 0; j< final_basis_num;j++) {
          basis_split1[ELT(numRows1,i,j)]  = basis_generator->non_linear_modes_[ELT(numRows,i,j)];
      }
  }
  sprintf(file_name_, "%s.basis_1.bin", basis_prefix);
  WriteBasisInBinary(file_name_, domain_offset_toggle_, final_basis_num, basis_split1);

  double *basis_split2 = new double[numRows2 * final_basis_num];
  for(int i = 0; i < numRows2; i++) {
      for(int j = 0; j< final_basis_num;j++) {
          basis_split2[ELT(numRows2,i,j)]  = basis_generator->non_linear_modes_[ELT(numRows,i+numRows1,j)];
      }
  }
  sprintf(file_name_, "%s.basis_2.bin", basis_prefix);
  WriteBasisInBinary(file_name_, vertex_num_-domain_offset_toggle_, final_basis_num, basis_split2);
  sprintf(file_name_, "%s.basis_2.txt", basis_prefix);
  WriteBasisInText(file_name_,vertex_num_-domain_offset_toggle_, final_basis_num, basis_split2);

  sprintf(file_name_, "%s.nonlin_weights.bin", basis_prefix);
  dj::Write1DVectorBinary(file_name_, basis_generator->eigen_values_);

  sprintf(file_name_, "%s.pure_eigen_vals.bin", basis_prefix);
  P(file_name_);
  dj::Write1DVectorBinary(file_name_, basis_generator->pure_eigen_values_);

  sprintf(file_name_, "%s.pure_eigen_vecs.bin", basis_prefix);
  P(file_name_);
  dj::Write1DVectorBinary(file_name_, basis_generator->pure_eigen_vectors_);

  sprintf(file_name_, "%s.lin_freqs.bin", basis_prefix);
  P(file_name_);
  dj::Write1DVectorBinary(file_name_, basis_generator->frequencies_);

  /*
  sprintf(file_name_, "%s.eigen_value.txt", basis_prefix);
  P(file_name_);
  dj::Write1DVectorText(file_name_, basis_generator->eigen_values_);

}

void SingleDomainBasisGenerator::SetFixedVertex(std::function<bool (int, double *)> IsFixed) {
  fixed_verts_.clear();
  for (int v = 0; v < vertex_num_; ++v) {
    if (IsFixed(v, X + v * 3)) {
      fixed_verts_.push_back(v);
      //      P(v, dj::Vec3d(X + v * 3));
    }
  }
  //  P(fixed_verts_.size());
}

void SingleDomainBasisGenerator::SetFixedVertex(std::vector<int> fixed_verts) {
  fixed_verts_ = fixed_verts;
}

void SingleDomainBasisGenerator::SetFixedVertex(int fixed_vert_num) {
  //  P(dj::Vec3d(&center_of_mass_[0]));
  typedef std::pair<double, int> Pair;
  struct Comparator {
    bool operator()(const Pair& a, const Pair& b) const {
      return a.first < b.first;
    }
  };

  std::fill(is_constrainted_.begin(), is_constrainted_.end(), 0);
  std::priority_queue<Pair, std::vector<Pair>, Comparator> queue;
  for (int v = 0; v < vertex_num_; ++v) {
    MapVec3 pos(rest_pos_ + v * 3);
    double distance = (pos - center_of_mass_).norm();
    if (int(queue.size()) < fixed_vert_num) {
      queue.push(Pair(distance, v));
    } else {
      if (distance < queue.top().first) {
        queue.pop();
        queue.push(Pair(distance, v));
      }
    }
  }

  fixed_verts_.clear();
  while (queue.size() != 0) {
    is_constrainted_[queue.top().second] = true;
    fixed_verts_.push_back(queue.top().second);
    queue.pop();
  }
}

SingleDomainBasisGenerator::~SingleDomainBasisGenerator() {
}


void SingleDomainBasisGenerator::RegenerateStitchBasis(int modeID) {
    basis_generator->RegenerateAllModes(modeID);
}

void SingleDomainBasisGenerator::setStitchedStiffnessMatrix(SparseMatrix *spmat) {
    basis_generator->setStitchStiffnessMatrix(spmat);
}
*/
