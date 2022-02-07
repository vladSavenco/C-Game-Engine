assetList = {
	gameObj1 = {
		objId = 1,
		isPlayer=false,
		isEnemy=true,
		enemyTyp=1,
		objMesh="chicken.obj",
		objTex="chicken.png",
		objPos ={
			X=-50.0,
			Y=5.0,
			Z=-5.0
		},
		objRot ={
			X=0.0,
			Y=0.0,
			Z=0.0
		},
		objScale ={
			X=5.0,
			Y=5.0,
			Z=5.0
		},
		objCollider={
			type="box",
			isStatic=false,
			rad=0,
			len=10,
			wid=5,
			hei=7
		}
	},
	gameObj2 = {
		objId = 2,
		isPlayer=false,
		isEnemy=true,
		enemyTyp=0,
		objMesh="doge.obj",
		objTex="doge.jpg",
		objPos ={
			X=50.0,
			Y=5.0,
			Z=-5.0
		},
		objRot ={
			X=0.0,
			Y=0.0,
			Z=0.0
		},
		objScale ={
			X=0.5,
			Y=0.5,
			Z=0.5
		},
		objCollider={
			type="box",
			isStatic=false,
			rad=0,
			len=10,
			wid=5,
			hei=7
		}
	},
	gameObj3 = {
		objId = 3,
		isPlayer=true,
		isEnemy=false,
		enemyTyp=0,
		objMesh="doge.obj",
		objTex="doge.jpg",
		objPos ={
			X=0.0,
			Y=5.0,
			Z=-5.0
		},
		objRot ={
			X=0.0,
			Y=0.0,
			Z=0.0
		},
		objScale ={
			X=0.5,
			Y=0.5,
			Z=0.5
		},
		objCollider={
			type="box",
			isStatic=false,
			rad=0,
			len=10,
			wid=5,
			hei=7
		}
	},
	gameObj4 = {
		objId = 4,
		isPlayer=false,
		isEnemy=false,
		enemyTyp=0,
		objMesh="dHouse.obj",
		objTex="dHouse.jpg",
		objPos ={
			X=0.0,
			Y=1.0,
			Z=-100.0
		},
		objRot ={
			X=0.0,
			Y=0.0,
			Z=0.0
		},
		objScale ={
			X=0.5,
			Y=0.5,
			Z=0.5
		},
		objCollider={
			type="box",
			isStatic=true,
			rad=0,
			len=15,
			wid=20,
			hei=15
		}
	},
	gameObj5 = {
		objId = 5,
		isPlayer=false,
		isEnemy=false,
		enemyTyp=0,
		objMesh="dHouse.obj",
		objTex="dHouse.jpg",
		objPos ={
			X=0.0,
			Y=1.0,
			Z=100.0
		},
		objRot ={
			X=0.0,
			Y=180.0,
			Z=0.0
		},
		objScale ={
			X=0.5,
			Y=0.5,
			Z=0.5
		},
		objCollider={
			type="box",
			isStatic=true,
			rad=0,
			len=15,
			wid=20,
			hei=15
		}
	}
}

plane={
	objMesh="grass.obj",
	objTex="grass.jpg",
}

aiList = {
	aiBehav1={
		id=0,
		detectR=500.0,
		dammage=2
	},
	aiBehav2={
		id=1,
		detectR=1000.0,
		dammage=1
	}
}

playerData={
	health=400,
	potions=5,
	potionEff=15
}

mainTheme={
	mus="Data/Music/gal.wav"
}

stepSound={
	stp="Data/Sounds/step.wav"
}