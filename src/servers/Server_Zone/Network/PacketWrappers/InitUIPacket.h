#ifndef _CORE_NETWORK_PACKETS_INITUIPACKET_H
#define _CORE_NETWORK_PACKETS_INITUIPACKET_H

#include <src/servers/Server_Common/Network/GamePacketNew.h>
#include <src/servers/Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>
#include "Server_Zone/Actor/Player.h"
#include "Server_Zone/Forwards.h"

namespace Core {
namespace Network {
namespace Packets {
namespace Server {

/**
* @brief The Client UI Initialization packet. This must be sent to the client
* once upon connection to configure the UI.
*/
class InitUIPacket : public GamePacketNew< FFXIVIpcInitUI, ServerZoneIpcType >
{
public:
   InitUIPacket( Entity::PlayerPtr player ) :
      GamePacketNew< FFXIVIpcInitUI, ServerZoneIpcType >( player->getId(), player->getId() )
   {
      initialize( player );
   };

private:
   void initialize( Entity::PlayerPtr player )
   {
      m_data.contentId = player->getContentId();

      // TODO: Support rested experience.
      m_data.restedExp = 0;
      //m_data.padding = 0x100;
      m_data.charId = player->getId();
      m_data.race = player->getLookAt( Common::CharaLook::Race );
      m_data.tribe = player->getLookAt( Common::CharaLook::Tribe );
      m_data.gender = player->getLookAt( Common::CharaLook::Gender );
      m_data.currentClass = static_cast< uint8_t >( player->getClass() );
      m_data.currentJob = static_cast< uint8_t >( player->getClass() );
      m_data.deity = static_cast< uint8_t >( player->getGuardianDeity() );
      m_data.namedayMonth = player->getBirthMonth();
      m_data.namedayDay = player->getBirthDay();
      // TODO: Support grand company status.
      m_data.grandCompany = static_cast< Common::GrandCompany >( player->getGc() );
      //m_data.gcRank = GCRank::None;

      // TODO: Support starting city.
      //m_data.startCity = Town::Gridania;
      m_data.homepoint = player->getHomepoint();

      memset( &m_data.name[0], 0, sizeof( m_data.name ) );

      strcpy( &m_data.name[0], player->getName().c_str() );

      memcpy( m_data.aetheryte, player->getAetheryteArray(), sizeof ( m_data.aetheryte ) );

      // Set the class levels and exp.
      for( uint8_t i = 0; i < 25; i++ )
      {
         m_data.levels[i] = player->getClassArray()[i];
         m_data.exp[i] = player->getExpArray()[i];
      }

      memcpy( m_data.orchestrionMask, player->getOrchestrionBitmask(), sizeof( m_data.orchestrionMask ) );

      memset( m_data.mountGuideMask, 0xFF, sizeof( m_data.mountGuideMask) );
      memset( m_data.fishingGuideMask, 0xFF, sizeof( m_data.fishingGuideMask ) );

      memcpy( m_data.unlockBitmask, player->getUnlockBitmask(), sizeof( m_data.unlockBitmask ) );

      memcpy( m_data.discovery, player->getDiscoveryBitmask(), sizeof( m_data.discovery ) );

      memcpy( m_data.howto, player->getHowToArray(), sizeof( m_data.howto ) );

      m_data.unknown_13 = 0x46;
      m_data.expansion = 2;

      //memset( m_data.unlockBitmask, 0xFF, sizeof( m_data.unlockBitmask )  );
      //memset( m_data.unknown_0344, 0xFF, sizeof( m_data.unknown_0344 ) );
      //memset( m_data.unknown_F4, 0xFF, sizeof( m_data.unknown_F4 ) );
      //m_data.pos.x = player->getPos().getX();
      //m_data.pos.y = player->getPos().getY();
      //m_data.pos.z = player->getPos().getZ();

   };
};

}
}
}
}

#endif /*_CORE_NETWORK_PACKETS_CINITUIPACKET_H*/
