#pragma once
#include "InputHandler.h"
#include "SplineGenerator.h"
#include "Bezier/MovingBezierSpline.h"

class Scene : public sf::Drawable
{

public:
	Scene(sf::RenderWindow* window, InputHandler* inputHandler);

	void Update(float dt);

	void SetGenerate(bool value);

	void SetMouseFollowing(bool value) { _isMouseFollowing = value; }

	void MovePosition(sf::Vector2f vec);

	sf::Vector2f GetPositionsCentroid() const;

	void Reset();	

	const std::vector<MovingBezierSpline>& GetSplines() const {return _splines;}

	void GenerateSpline();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void ResetSpline(MovingBezierSpline& spline) const;
	void UpdateWindowViewCenter(float dt);
	sf::Vector2f GetMouseWorldPosition() const;

		
	std::vector<MovingBezierSpline> _splines;

	sf::RenderWindow* _window;

	InputHandler* _inputHandler;

	bool _isGenerate;
	SplineGenerator	_splineGenerator;

	bool _isMouseFollowing;

};
