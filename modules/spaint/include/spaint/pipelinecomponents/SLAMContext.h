/**
 * spaint: SLAMContext.h
 * Copyright (c) Torr Vision Group, University of Oxford, 2016. All rights reserved.
 */

#ifndef H_SPAINT_SLAMCONTEXT
#define H_SPAINT_SLAMCONTEXT

#include <boost/shared_ptr.hpp>

#include <ITMLib/Engines/Visualisation/Interface/ITMVisualisationEngine.h>

#include "../util/SpaintVoxel.h"

namespace spaint {

/**
* \brief An instance of a class deriving from this one provides the shared context needed by a SLAM component.
*/
class SLAMContext
{
  //#################### TYPEDEFS ####################
private:
  typedef boost::shared_ptr<ITMLib::ITMView> View_Ptr;
  typedef boost::shared_ptr<const ITMLib::ITMVisualisationEngine<SpaintVoxel,ITMVoxelIndex> > VisualisationEngine_CPtr;

  //#################### DESTRUCTOR ####################
public:
  /**
   * \brief Destroys the SLAM context.
   */
  virtual ~SLAMContext() {}

  //#################### PUBLIC ABSTRACT MEMBER FUNCTIONS ####################
public:
  /**
   * \brief Gets the current view of the scene.
   *
   * \return  The current view of the scene.
   */
  virtual const View_Ptr& get_view() = 0;

  /**
   * \brief Gets the InfiniTAM engine used for raycasting the scene.
   *
   * \return  The InfiniTAM engine used for raycasting the scene.
   */
  virtual VisualisationEngine_CPtr get_visualisation_engine() const = 0;

  /**
   * \brief Sets the current view of the scene.
   *
   * \param view  The new current view of the scene.
   */
  virtual void set_view(ITMLib::ITMView *view) = 0;
};

}

#endif
