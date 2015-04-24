/**
 * spaint: VoxelMarker_CUDA.h
 */

#ifndef H_SPAINT_VOXELMARKER_CUDA
#define H_SPAINT_VOXELMARKER_CUDA

#include "../interface/VoxelMarker.h"

namespace spaint {

/**
 * \brief An instance of this class can be used to mark a set of voxels with a semantic label using CUDA.
 */
class VoxelMarker_CUDA : public VoxelMarker
{
  //#################### PUBLIC MEMBER FUNCTIONS ####################
public:
  /** Override */
  virtual void clear_labels(SpaintVoxel *voxels, int voxelCount) const;

  /** Override */
  virtual void mark_voxels(const ORUtils::MemoryBlock<Vector3s>& voxelLocationsMB, SpaintVoxel::LabelType label,
                           ITMLib::Objects::ITMScene<SpaintVoxel,ITMVoxelIndex> *scene,
                           ORUtils::MemoryBlock<SpaintVoxel::LabelType> *oldVoxelLabelsMB) const;

  /** Override */
  virtual void mark_voxels(const ORUtils::MemoryBlock<Vector3s>& voxelLocationsMB,
                           const ORUtils::MemoryBlock<SpaintVoxel::LabelType>& voxelLabelsMB,
                           ITMLib::Objects::ITMScene<SpaintVoxel,ITMVoxelIndex> *scene,
                           ORUtils::MemoryBlock<SpaintVoxel::LabelType> *oldVoxelLabelsMB) const;
};

}

#endif