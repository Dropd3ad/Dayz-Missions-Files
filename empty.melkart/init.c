void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();				

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
}

const string TOURIST = "tourist";
const string RURAL = "rural";
const string VILLAGER = "villager";
const string TOWNSPERSON = "townsperson";
const string CITYPERSON = "cityperson";

const string PLAYER_CLASSES[] = {TOURIST, RURAL, VILLAGER, TOWNSPERSON, CITYPERSON};

// HEAD CLOTHING OPTIONS:
const string FLAT_CAPS[] = {"FlatCap_Black", "FlatCap_BlackCheck", "FlatCap_Blue", "FlatCap_Brown", "FlatCap_BrownCheck", "FlatCap_Grey", "FlatCap_GreyCheck", "FlatCap_Red"};

// TORSO CLOTHING OPTIONS:
const string TSHIRTS[] = {"TShirt_Beige", "TShirt_Black", "TShirt_Blue", "TShirt_Green", "TShirt_Grey", "TShirt_OrangeWhiteStripes", "TShirt_Red", "TShirt_RedBlackStripes", "TShirt_White"};
const string RAGLAN_SHIRTS[] = {"Medium_Sleeves_Shirt", "Medium_Sleeves_Shirt_Red", "Medium_Sleeves_Shirt_Blue"}; // WINDSTRIDE
const string LAYERED_SHIRTS[] = {"Layered_Shirt_Base", "Layered_Shirt_White", "Layered_Shirt_Cheburashka", "Layered_Shirt_Courage", "Layered_Shirt_Lily"}; // WINDSTRIDE
const string QUILTED_JACKETS[] = {"QuiltedJacket_Black", "QuiltedJacket_Blue", "QuiltedJacket_Green", "QuiltedJacket_Grey", "QuiltedJacket_Orange", "QuiltedJacket_Red", "QuiltedJacket_Violet", "QuiltedJacket_Yellow"};
const string TRACK_JACKETS[] = {"TrackSuitJacket_Black","TrackSuitJacket_Blue","TrackSuitJacket_Green","TrackSuitJacket_LightBlue","TrackSuitJacket_Red"};

// LEGS CLOTHING OPTIONS:
const string TRACK_PANTS[] = {"TrackSuitPants_Black", "TrackSuitPants_Blue", "TrackSuitPants_Green", "TrackSuitPants_LightBlue", "TrackSuitPants_Red"};
const string HIKING_PANTS[] = {"CanvasPants_Beige", "CanvasPants_Blue", "CanvasPants_Grey", "CanvasPants_Red", "CanvasPants_Violet"};
const string JEANS[] = {"Jeans_Black","Jeans_Blue","Jeans_BlueDark","Jeans_Brown","Jeans_Green","Jeans_Grey"};

// FEET CLOTHING OPTIONS:
const string RUNNING_SHOES[] = {"JoggingShoes_Black", "JoggingShoes_Blue", "JoggingShoes_Red", "JoggingShoes_Violet", "JoggingShoes_White"};
const string WELLIES[] = {"Wellies_Black", "Wellies_Brown", "Wellies_Green", "Wellies_Grey"};
const string FLIP_FLOPS = "FlipFlops_Colorbase";

// BAG OPTIONS:
const string CANVAS_BACKPACKS[] = {"Canvas_Backpack_Base", "Canvas_Backpack_Black", "Canvas_Backpack_White", "Canvas_Backpack_Red", "Canvas_Backpack_Blue", "Canvas_Backpack_Purple"}; // WINDSTRIDE

class CustomMission: MissionServer
{
	void setRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.45, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	void spawnItemNTimesOnPlayer(PlayerBase player, string item, int n) {
        for(int i = 0; i < n; i++) {
            player.GetInventory().CreateInInventory(item);
        }
    }

    void spawnItemsOnPlayer(PlayerBase player, TStringArray items, bool withDamage) {
        for(int i = 0; i < items.Count(); i++) {
             EntityAI itemEnt = player.GetInventory().CreateInInventory(items[i]);

            if(withDamage) {
                setRandomHealth(itemEnt);
            }
        }
    }

    void spawnItemWithAttachments(PlayerBase player, string parentItem, TStringArray attachments) {
        EntityAI itemEnt;
        
        itemEnt = player.GetInventory().CreateInInventory(parentItem);

        for(int i = 0; i < attachments.Count(); i++) {
            itemEnt.GetInventory().CreateAttachment(attachments[i]);
        }   
    }

    string pickPlayerClass() {
        int i = Math.RandomInt(0, 5);

        return PLAYER_CLASSES[i];
    }

    void spawnTourist(PlayerBase player) {
        int i = Math.RandomInt(0, 9);
        string torso = TSHIRTS[i];

        i = Math.RandomInt(0, 6);
        string legs = JEANS[i];

        i = Math.RandomInt(0, 5);
        string feet = RUNNING_SHOES[i];

        i = Math.RandomInt(0, 6);
        string bag = CANVAS_BACKPACKS[i];

        autoptr TStringArray playerItems = {torso, legs, feet, bag};

        spawnItemsOnPlayer(player, playerItems, true);

        player.GetInventory().CreateInInventory("ZagorkyChocolate");
        player.GetInventory().CreateInInventory("WaterBottle");
    }

    void spawnRural(PlayerBase player) {
        string bladedTools[] = {"CrudeMachete", "Machete", "Hatchet"};

        int i = Math.RandomInt(0, 8);
        string torso = QUILTED_JACKETS[i];

        i = Math.RandomInt(0, 5);
        string legs = HIKING_PANTS[i];

        i = Math.RandomInt(0, 4);
        string feet = WELLIES[i];

        i = Math.RandomInt(0, 3);
        string tool = bladedTools[i];

        autoptr TStringArray playerItems = {torso, legs, feet, tool};

        spawnItemsOnPlayer(player, playerItems, true);
    }

    void spawnVillager(PlayerBase player) {
        int i = Math.RandomInt(0, 5);
        string torso = TRACK_JACKETS[i];
        // use same index for track pants so they match
        string legs = TRACK_PANTS[i];

        i = Math.RandomInt(0, 8);
        string head = FLAT_CAPS[i];
        string feet = FLIP_FLOPS;

        autoptr TStringArray playerItems = {torso, legs, feet, head};

        spawnItemsOnPlayer(player, playerItems, true);

        player.GetInventory().CreateInInventory("PetrolLighter");
        player.GetInventory().CreateInInventory("SodaCan_Kvass");
    }

    // void spawnTownsperson(PlayerBase player) {

    // }

    // void spawnCityperson(PlayerBase player) {

    // }

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemClothing = player.FindAttachmentBySlotName( "Body" );

		if ( itemClothing )
		{
			player.RemoveAllItems();
            
            string playerClass = pickPlayerClass();

            spawnTourist(player);

            switch(playerClass){
                case TOURIST:
                    spawnTourist(player);
                    break;
                case RURAL:
                    spawnRural(player);
                    break;
                case VILLAGER:
                    spawnVillager(player);
                    break;
                case TOWNSPERSON:
                    spawnRural(player);
                    break;
                case CITYPERSON:
                    spawnVillager(player);
                    break;
            }

            // Universal items

			itemEnt = player.GetInventory().CreateInInventory( "BandageDressing" );
		}
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}