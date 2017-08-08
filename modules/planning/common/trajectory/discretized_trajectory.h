/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file discretized_trajectory.h
 **/

#ifndef MODULES_PLANNING_COMMON_TRAJECTORY_DISCRETIZED_TRAJECTORY_H
#define MODULES_PLANNING_COMMON_TRAJECTORY_DISCRETIZED_TRAJECTORY_H

#include <vector>

#include "modules/common/math/vec2d.h"
#include "modules/planning/common/trajectory/trajectory.h"
#include "glog/logging.h"

namespace apollo {
namespace planning {

class DiscretizedTrajectory : public Trajectory {
 public:
  DiscretizedTrajectory() = default;

  DiscretizedTrajectory(
      std::vector<common::TrajectoryPoint> trajectory_points);

  virtual ~DiscretizedTrajectory() = default;

  double TimeLength() const override;

  common::TrajectoryPoint Evaluate(
      const double relative_time) const override;

  common::TrajectoryPoint StartPoint() const override;

  common::TrajectoryPoint EndPoint() const override;

  virtual common::TrajectoryPoint EvaluateUsingLinearApproximation(
      const double relative_time) const;

  virtual uint32_t QueryNearestPoint(const double relative_time) const;

  virtual uint32_t QueryNearestPoint(
      const common::math::Vec2d& position) const;

  virtual void AppendTrajectoryPoint(
      const common::TrajectoryPoint& trajectory_point);

  template <typename Iter>
  void PrependTrajectoryPoints(Iter begin, Iter end) {
    if (!_trajectory_points.empty() && begin != end) {
      CHECK((end - 1)->relative_time() < _trajectory_points.front().relative_time());
    }
    _trajectory_points.insert(_trajectory_points.begin(), begin, end);
  }

  const common::TrajectoryPoint& TrajectoryPointAt(
      const std::uint32_t index) const;

  uint32_t NumOfPoints() const;

  void SetTrajectoryPoints(
      const std::vector<common::TrajectoryPoint>& points);

  const std::vector<common::TrajectoryPoint>& trajectory_points() const;

  virtual void Clear();

 protected:
  std::vector<common::TrajectoryPoint> _trajectory_points;
};

}  // namespace planning
}  // namespace apollo

#endif  // MODULES_PLANNING_COMMON_TRAJECTORY_DISCRETIZED_TRAJECTORY_H
