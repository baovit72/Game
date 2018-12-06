#include"MegamanBullet3.h"


MegamanBullet3::MegamanBullet3(float x, float y, Direction d)
{
	this->destroyed = false;

	this->x = x;
	this->y = y;
	this->direction = d;
	this->SetState(SHOOTING);

	MyTexture *texture = TXT::Instance()->GetTexture(TBULLETMEGAMAN);
	vector<RECT*> list_source_rect_shooting = TXT::Instance()->GetListSourceRect(SBULLET3MEGAMANSTART);
	animation->listSprite[SHOOTING] = new Sprite(texture, list_source_rect_shooting, 1);

	vector<RECT*> list_source_rect_destroy = TXT::Instance()->GetListSourceRect(SBULLET3MEGAMANDESTROY);
	animation->listSprite[DESTROYBULLET] = new Sprite(texture, list_source_rect_destroy, 1);
}

MegamanBullet3::~MegamanBullet3()
{
}

void MegamanBullet3::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	if (this->distance_has_shot_x > 600 || (this->state == DESTROYBULLET && this->animation->listSprite[state]->IsFinalFrame()))
	{
		this->destroyed = true;
		return;
	}

	Object::Update(dt, List_object_can_col);
	this->distance_has_shot_x += dx;

	bool check_coll = false;
	for (Object* O : *List_object_can_col) {
		ResultCollision r;
		r = Collision::Instance()->CollisionSweptAABB(this->GetBoundingBox(), O->GetBoundingBox());
		if (r.isCollision)
		{
			check_coll = true;
			float x_temp, y_temp;

			O->GetPosition(x_temp, y_temp);
			O->SetPosition(x_temp + 10, y_temp);

			this->SetPosition(x_temp + 5, y);
			this->SetState(DESTROYBULLET);
		}

	}

	if (!check_coll)
	{
		x += dx;
		//y += dy;
	}
}

void MegamanBullet3::Render()
{
	//G_Scale = D3DXVECTOR2(1, 1);
	//G_ScaleFlipX = D3DXVECTOR2(-1, 1);
	Bullet::Render();
	//G_Scale = D3DXVECTOR2(2.5, 2.5);
	//G_ScaleFlipX = D3DXVECTOR2(-2.5, 2.5);
}

BoundingBox MegamanBullet3::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - MEGAMAN_BULLET3_WIDTH / 2;
	bound.y = y - MEGAMAN_BULLET3_HEIGHT / 2;
	bound.w = MEGAMAN_BULLET3_WIDTH;
	bound.h = MEGAMAN_BULLET3_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void MegamanBullet3::SetState(State s)
{
	this->state = s;
	switch (s)
	{
	case SHOOTING:
		vx = (this->direction == RIGHT) ? MEGAMAN_BULLET3_VX : -MEGAMAN_BULLET3_VX;
		vy = MEGAMAN_BULLET3_VY;
		break;

	case DESTROYBULLET:
		vx = vy = 0;
		break;
	default:
		break;
	}
}

void MegamanBullet3::SetDirection(Direction d)
{
	this->direction = d;
}

bool MegamanBullet3::IsDestroyed()
{
	return this->destroyed;
}