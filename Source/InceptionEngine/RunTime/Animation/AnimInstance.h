
#pragma once
#include "AnimSpeedBar.h"
#include "ECS/Components/AnimationComponent/AnimNotify.h"
#include "ECS/Components/AnimationComponent/AnimNotifyState.h"

namespace inceptionengine
{
	struct Animation;
	struct EventAnimPlaySetting;

	enum class AnimInterpType
	{
		Linear,
		Step
	};

	class AnimInstance
	{
	public:
		AnimInstance(std::string const& animFilePath);

		AnimInstance(EventAnimPlaySetting const& setting);

		~AnimInstance();

		std::vector<Matrix4x4f> Sample(float time, AnimInterpType interpType = AnimInterpType::Linear);

		float GetDuration() const;

		void Start();

		void End();

		void Interrupt();

		void Notify(float time);

		float QueryAnimSpeed(float ratio) const;

		float GetBlendOutDuration() const;

		void InsertAnimSpeedRange(AnimSpeedRange const& range);

		
	private:
		AnimInterpType mInterpType = AnimInterpType::Linear;

		std::shared_ptr<Animation const> mAnimationResource;

		std::string mAnimationFilePath;

		bool mRootMotion = false;
		AnimSpeedBar mAnimSpeedBar;
		std::function<void()> mAnimStartCallback;
		std::function<void()> mAnimInterruptCallback;
		std::function<void()> mAnimEndCallback;
		std::list<AnimNotify> mAnimNotifies;
		std::vector<AnimNotifyState> mAnimNotifyStates;

		float mBlendInDuration = 0.05f;
		float mBlendOutDuration = 0.05f;


	};
}