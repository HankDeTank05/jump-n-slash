import os
import json
import jnscommon as jns 

class TileDetailsModel:
    
    # Manages tile data, loads from JSON, and provides structured data for the VIEW.
    

    def __init__(self):
        self.tile_data = {}

    def load_tile_data(self, tile_name: str) -> dict:
        # Loads tile properties from a JSON file. tile_name: The name of the tile without prefix or file extension. Returns A dictionary with tile properties.
        
        tile_base_name = jns.ConvertToCamelCase(tile_name.replace(".png", ""))
        tile_json_path = os.path.join(jns.READ_LOCATION_TEXTURES_LEVELTILES, tile_base_name + "_data.json")

        if os.path.exists(tile_json_path):
            with open(tile_json_path, "r") as json_file:
                self.tile_data = json.load(json_file)
        else:
            print(f"Warning: No JSON data found for tile: {tile_base_name}")
            self.tile_data = {}  # Reset data

        return self.tile_data