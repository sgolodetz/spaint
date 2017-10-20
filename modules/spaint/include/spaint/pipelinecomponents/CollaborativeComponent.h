/**
 * spaint: CollaborativeComponent.h
 * Copyright (c) Torr Vision Group, University of Oxford, 2017. All rights reserved.
 */

#ifndef H_SPAINT_COLLABORATIVECOMPONENT
#define H_SPAINT_COLLABORATIVECOMPONENT

#include <boost/atomic.hpp>
#include <boost/thread.hpp>

#include <tvgutil/numbers/RandomNumberGenerator.h>

#include "CollaborativeContext.h"
#include "../collaboration/SubmapRelocalisation.h"

namespace spaint {

/**
 * \brief An instance of this pipeline component can be used to determine the relative poses between agents participating in collaborative SLAM.
 */
class CollaborativeComponent
{
  //#################### ENUMERATIONS ####################
public:
  /**
   * \brief TODO
   */
  enum Mode
  {
    /** TODO */
    MODE_BATCH,

    /** TODO */
    MODE_LIVE
  };

  //#################### TYPEDEFS ####################
private:
  typedef boost::shared_ptr<SubmapRelocalisation> SubmapRelocalisation_Ptr;
  typedef std::pair<SubmapRelocalisation_Ptr,float> Candidate;

  //#################### PRIVATE VARIABLES ####################
private:
  /** TODO */
  SubmapRelocalisation_Ptr m_bestCandidate;

  /** The shared context needed for collaborative SLAM. */
  CollaborativeContext_Ptr m_context;

  /** TODO */
  int m_frameIndex;

  /** TODO */
  Mode m_mode;

  /** TODO */
  boost::mutex m_mutex;

  /** TODO */
  boost::condition_variable m_readyToRelocalise;

  /** TODO */
  boost::thread m_relocalisationThread;

  /** A random number generator. */
  mutable tvgutil::RandomNumberGenerator m_rng;

  /** TODO */
  boost::atomic<bool> m_stopRelocalisationThread;

  /** TODO */
  std::map<std::string,std::deque<ORUtils::SE3Pose> > m_trajectories;

  /** TODO */
  std::map<std::pair<std::string,std::string>,std::deque<ORUtils::SE3Pose> > m_triedPoses;

  //#################### CONSTRUCTORS ####################
public:
  /**
   * \brief Constructs a collaborative component.
   *
   * \param context The shared context needed for collaborative SLAM.
   * \param mode    TODO
   */
  CollaborativeComponent(const CollaborativeContext_Ptr& context, Mode mode = MODE_LIVE);

  //#################### DESTRUCTOR ####################
public:
  /**
   * \brief Destroys the collaborative component.
   */
  ~CollaborativeComponent();

  //#################### PUBLIC MEMBER FUNCTIONS ####################
public:
  /**
   * \brief TODO
   */
  void run_collaborative_pose_estimation();

  //#################### PRIVATE MEMBER FUNCTIONS ####################
private:
  /**
   * \brief TODO
   */
  std::list<Candidate> generate_random_candidates(size_t desiredCandidateCount) const;

  /**
   * \brief TODO
   */
  void run_relocalisation();

  /**
   * \brief TODO
   */
  void score_candidates(std::list<Candidate>& candidates) const;

  /**
   * \brief TODO
   */
  void try_schedule_relocalisation();

  /**
   * \brief TODO
   */
  bool update_trajectories();
};

//#################### TYPEDEFS ####################

typedef boost::shared_ptr<CollaborativeComponent> CollaborativeComponent_Ptr;

}

#endif
