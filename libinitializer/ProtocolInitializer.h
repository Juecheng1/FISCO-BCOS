/**
 *  Copyright (C) 2021 FISCO BCOS.
 *  SPDX-License-Identifier: Apache-2.0
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * @brief initializer for the protocol module
 * @file ProtocolInitializer.h
 * @author: yujiechen
 * @date 2021-06-10
 */
#pragma once
#include <bcos-crypto/interfaces/crypto/CryptoSuite.h>
#include <bcos-crypto/interfaces/crypto/KeyFactory.h>
#include <bcos-framework/protocol/BlockFactory.h>
#include <bcos-framework/protocol/TransactionSubmitResultFactory.h>
#include <bcos-framework/security/StorageEncryptInterface.h>
#include <bcos-framework/security/KeyEncryptInterface.h>
#include <bcos-tool/NodeConfig.h>

namespace bcos::initializer
{
class ProtocolInitializer
{
public:
    using Ptr = std::shared_ptr<ProtocolInitializer>;
    ProtocolInitializer();
    virtual ~ProtocolInitializer() = default;

    virtual void init(bcos::tool::NodeConfig::Ptr _nodeConfig);
    void loadKeyPair(std::string const& _privateKeyPath);

    bcos::crypto::CryptoSuite::Ptr cryptoSuite() { return m_cryptoSuite; }
    bcos::protocol::BlockFactory::Ptr blockFactory() { return m_blockFactory; }
    bcos::protocol::TransactionSubmitResultFactory::Ptr txResultFactory()
    {
        return m_txResultFactory;
    }

    bcos::crypto::KeyPairInterface::Ptr keyPair() const { return m_keyPair; }
    // bool enableHsm() const { return m_enableHsm; }
    const std::string& hsmLibPath() const { return m_hsmLibPath; }
    int keyIndex() const { return m_keyIndex; }
    const std::string& password() const { return m_password; }
    bcos::crypto::KeyFactory::Ptr keyFactory() const { return m_keyFactory; }
    bcos::security::KeyEncryptInterface::Ptr keyEncryption() const { return m_keyEncryption; }
    bcos::security::StorageEncryptInterface::Ptr dataEncryption() const { return m_dataEncryption; }
    bcos::security::KeyEncryptInterface::Ptr getKeyEncryptionByType(bcos::security::KeyEncryptionType _type);

private:
    void createCryptoSuite();
    void createSMCryptoSuite();
    void createHsmSMCryptoSuite();

private:
    bcos::crypto::KeyFactory::Ptr m_keyFactory;
    bcos::crypto::CryptoSuite::Ptr m_cryptoSuite;
    bcos::protocol::BlockFactory::Ptr m_blockFactory;
    bcos::protocol::TransactionSubmitResultFactory::Ptr m_txResultFactory;
    bcos::crypto::KeyPairInterface::Ptr m_keyPair;
    size_t c_hexedPrivateKeySize = 64;
    bcos::security::KeyEncryptionType m_keyEncryptionType;
    // bool m_enableHsm;
    bcos::security::KeyEncryptInterface::Ptr m_keyEncryption{nullptr};
    bcos::security::StorageEncryptInterface::Ptr m_dataEncryption{nullptr};
    std::string m_hsmLibPath;
    int m_keyIndex;
    std::string m_password;
};
}  // namespace bcos::initializer