/**
 * spaint: SLAMContext.h
 * Copyright (c) Torr Vision Group, University of Oxford, 2016. All rights reserved.
 */

#ifndef H_SPAINT_SLAMCONTEXT
#define H_SPAINT_SLAMCONTEXT

#include <map>

#include <ITMLib/Engines/Visualisation/Interface/ITMSurfelVisualisationEngine.h>
#include <ITMLib/Engines/Visualisation/Interface/ITMVisualisationEngine.h>

#include <itmx/relocalisation/RefiningRelocaliser.h>
#include <itmx/remotemapping/MappingClient.h>
#include <itmx/remotemapping/MappingServer.h>

#include "../slamstate/SLAMState.h"

namespace spaint {

/**
 * \brief An instance of a class deriving from this one provides the shared context needed by SLAM components.
 */
class SLAMContext
{
  //#################### TYPEDEFS ####################
private:
  typedef boost::shared_ptr<const ITMLib::ITMSurfelVisualisationEngine<SpaintSurfel> > SurfelVisualisationEngine_CPtr;
  typedef boost::shared_ptr<const ITMLib::ITMVisualisationEngine<SpaintVoxel,ITMVoxelIndex> > VoxelVisualisationEngine_CPtr;

  //#################### PRIVATE VARIABLES ####################
private:
  /** The mapping clients (if any) to use to communicate with the remote mapping server regarding the various scenes. */
  std::map<std::string,itmx::MappingClient_Ptr> m_mappingClients;

  /** The relocalisers used to estimate the camera pose in the various scenes. */
  std::map<std::string,itmx::RefiningRelocaliser_Ptr> m_relocalisers;

  /** The IDs of all existing scenes. */
  std::vector<std::string> m_sceneIDs;

  /** The states of the SLAM reconstructions for the various scenes. */
  std::map<std::string,SLAMState_Ptr> m_slamStates;

  //#################### DESTRUCTOR ####################
public:
  /**
   * \brief Destroys the SLAM context.
   */
  virtual ~SLAMContext() {}

  //#################### PUBLIC ABSTRACT MEMBER FUNCTIONS ####################
public:
  virtual const itmx::MappingServer_Ptr& get_mapping_server() = 0;
  virtual const std::string& get_resources_dir() const = 0;
  virtual const Settings_CPtr& get_settings() const = 0;
  virtual SurfelVisualisationEngine_CPtr get_surfel_visualisation_engine() const = 0;
  virtual VoxelVisualisationEngine_CPtr get_voxel_visualisation_engine() const = 0;

  //#################### PUBLIC MEMBER FUNCTIONS ####################
public:
  /**
   * \brief Adds the specified scene ID to the list of existing scene IDs.
   *
   * \param sceneID The scene ID to add.
   */
  void add_scene_id(const std::string& sceneID);

  /**
   * \brief Gets the mapping client (if any) for the specified scene.
   *
   * \param sceneID The scene ID.
   * \return        The mapping client (if any) for the specified scene.
   */
  virtual itmx::MappingClient_Ptr& get_mapping_client(const std::string& sceneID);

  /**
   * \brief Gets the relocaliser for the specified scene.
   *
   * \param sceneID The scene ID.
   * \return        The relocaliser for the specified scene.
   */
  virtual itmx::RefiningRelocaliser_Ptr& get_relocaliser(const std::string& sceneID);

  /**
   * \brief Gets the relocaliser for the specified scene.
   *
   * \param sceneID The scene ID.
   * \return        The relocaliser for the specified scene.
   */
  virtual itmx::RefiningRelocaliser_CPtr get_relocaliser(const std::string& sceneID) const;

  /**
   * \brief Gets the IDs of all existing scenes.
   *
   * \return  The IDs of all existing scenes.
   */
  virtual const std::vector<std::string>& get_scene_ids() const;

  /**
   * \brief Gets the SLAM state for the specified scene.
   *
   * \param sceneID The scene ID.
   * \return        The SLAM state for the specified scene.
   */
  virtual const SLAMState_Ptr& get_slam_state(const std::string& sceneID);

  /**
   * \brief Gets the SLAM state for the specified scene (if any).
   *
   * \param sceneID The scene ID.
   * \return        The SLAM state for the specified scene (if any), or null otherwise.
   */
  virtual SLAMState_CPtr get_slam_state(const std::string& sceneID) const;
};

//#################### TYPEDEFS ####################

typedef boost::shared_ptr<SLAMContext> SLAMContext_Ptr;

}

#endif
